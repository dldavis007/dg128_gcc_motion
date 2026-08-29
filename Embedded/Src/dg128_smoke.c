#include "dg128_registers.h"
#include "motion_sequence.h"
#include "motion_csv.h"
#include "coating_cycle.h"
#include "coating_csv.h"
#include "noice_vuart.h"
#include "debug_visibility.h"

#define NEAR_FIXED __attribute__((near, section(".text.nonpaged")))

#define TIMER_TICKS_1MS 750u
#define PROX_INPUT_MASK 0x10u
#define PROX_QUALIFY_SAMPLES 2u
#define PROX_STOP_TIMEOUT_MS 3000ul
#define MOTOR_ENABLE_COMMAND_MASK 0x02u
#define MOTOR_ENABLE_FEEDBACK_MASK 0x08u
#define MOTOR_ARM_VALUE 0xA5u
#define MOTOR_DEFAULT_TIMEOUT_MS 5000ul
#define MOTOR_MAX_TIMEOUT_MS 60000ul
#define MOTION_ARM_VALUE 0xC3u
#define COATING_ARM_VALUE 0xD4u
#define COATING_COMMAND_GAP_MS 100ul
#define COATING_DEFAULT_HOME_DELAY_MS 1000ul

volatile unsigned long Tick1msCount;
volatile unsigned long Tick10msCount;
volatile unsigned long MainLoopCount;
volatile unsigned long ProxEdgeCount;
volatile unsigned long ProxLastRiseMs;
volatile unsigned long ProxPeriodMs;
volatile unsigned char ProxPeriodValid;
volatile unsigned char ProxInputRaw;
volatile unsigned char ProxInputStable;
volatile unsigned char ProxStopped;
volatile unsigned char StartupPassed;
volatile unsigned char MotorOutputsEnabled;
volatile unsigned char MotorEnableFeedback;
volatile signed char MotorTestDutyPercent;
volatile unsigned char MotorTestArm;
volatile unsigned char MotorTestStatus;
volatile unsigned long MotorTestTimeoutMs = MOTOR_DEFAULT_TIMEOUT_MS;
volatile unsigned long MotorTestElapsedMs;
volatile unsigned char MotionTestArm;
volatile unsigned char MotionState;
volatile unsigned char MotionCycle;
volatile unsigned char MotionFault;
volatile signed long MotionPositionCount;
volatile signed long MotionTargetCount;
volatile signed char MotionCommandDuty;
volatile signed int MotionPositionErrorCounts;
volatile signed int MotionSpeedCommandX100;
volatile signed int MotionMeasuredSpeedX100;
volatile signed int MotionSpeedErrorX100;
volatile signed int MotionSpeedIntegralX100;

/* NoICE-editable coating menu settings. Distances are tenths of an inch. */
volatile unsigned char CoatActuatorLengthTenths = 100u;
volatile unsigned char CoatShortStrokeCount = 4u;
volatile unsigned char CoatShortLengthTenths = 40u;
volatile unsigned char CoatLongStrokeCount = 4u;
volatile unsigned char CoatLongLengthTenths = 100u;
volatile unsigned char CoatPositioningSpeedPercent = 75u;
volatile unsigned char CoatHomingSpeedPercent = 35u;
volatile unsigned char CoatFastStrokeCount = 2u;
volatile unsigned char CoatShortFastSpeedPercent = 70u;
volatile unsigned char CoatShortSlowSpeedPercent = 40u;
volatile unsigned char CoatLongFastSpeedPercent = 90u;
volatile unsigned char CoatLongSlowSpeedPercent = 60u;
volatile unsigned int CoatFeedbackCountsPerInchX100 = 485u;
volatile unsigned int CoatMotorMaxSpeedCountsX100 = 625u;
volatile unsigned long CoatSimHomeDelayMs = COATING_DEFAULT_HOME_DELAY_MS;

/* Simulated CAN command/status process image and coating diagnostics. */
volatile unsigned char CoatingTestArm;
volatile unsigned char SimCanPositionTenths;
volatile unsigned char SimCanSpeedPercent;
volatile unsigned char SimCanCommandPending;
volatile unsigned char SimCanMoving;
volatile unsigned char SimCanFault;
volatile unsigned char CoatOperation;
volatile unsigned char CoatStrokeNumber;
volatile unsigned char CoatStrokeTotal;
volatile unsigned char CoatDirectionExtend;
volatile unsigned char CoatTargetTenths;
volatile unsigned char CoatSpeedPercent;
volatile unsigned char CoatAutomaticActive;

FILE_LOCAL unsigned long ProxPreviousRiseMs;
FILE_LOCAL unsigned char ProxFirstRising = 1u;
FILE_LOCAL unsigned char ProxCandidateState;
FILE_LOCAL unsigned char ProxQualifyCount;
FILE_LOCAL unsigned char Tick10msDivider;
FILE_LOCAL unsigned long MotorTestStartMs;
FILE_LOCAL volatile signed char MotorActiveDirection;
FILE_LOCAL MOTION_SEQUENCE MotionSequence;
FILE_LOCAL unsigned char MotionPreviousArm;
FILE_LOCAL unsigned char MotionAutomaticActive;
FILE_LOCAL unsigned long MotionLastControlTick;
FILE_LOCAL unsigned long MotionNextTelemetryMs;
FILE_LOCAL unsigned char MotionFinalTelemetrySent;
FILE_LOCAL char MotionTelemetryLine[96];
FILE_LOCAL COATING_SETTINGS EmbeddedCoatingSettings;
FILE_LOCAL COATING_CYCLE EmbeddedCoatingCycle;
FILE_LOCAL unsigned char CoatingPreviousArm;
FILE_LOCAL unsigned char SimCanPreviousPosition;
FILE_LOCAL unsigned char SimCanPreviousSpeed;
FILE_LOCAL unsigned long CoatingHomeStartMs;
FILE_LOCAL unsigned long CoatingNextCommandMs;
FILE_LOCAL unsigned long CoatingLastControlTick;
FILE_LOCAL char CoatingTelemetryLine[160];

/* Require two fresh rising edges before speed feedback is valid for a move. */
FILE_LOCAL void prox_speed_invalidate(void)
{
    ProxPeriodValid = 0u;
    ProxStopped = 1u;
    ProxFirstRising = 1u;
}

/*
 * pll_init
 * Configure the DG128 PLL for the board's 8 MHz crystal and select the locked
 * 24 MHz bus clock.  BDM tools must use 24 MHz after this function completes.
 * This routine blocks until LOCK is asserted and must run before timer setup.
 */
FILE_LOCAL void pll_init(void)
{
    /* Existing board configuration: 8 MHz crystal, 24 MHz bus. */
    REFDV = 5u;
    SYNR = 17u;
    while ((CRGFLG & PLL_LOCKED) == 0u) {
        /* Wait for lock before selecting the PLL clock. */
    }
    CLKSEL |= PLL_SELECT;
}

/*
 * default_isr
 * Catch every unassigned interrupt vector in nonpaged memory.  The deliberate
 * infinite loop leaves the processor at a stable address for NoICE diagnosis.
 */
void NEAR_FIXED default_isr(void)
{
    for (;;) {
        /* Stop here in NoICE if an unexpected vector is taken. */
    }
}

/*
 * timer_ch7_handler
 * Nonpaged 1 ms heartbeat ISR.  It schedules the next TC7 compare, maintains
 * the millisecond/10-millisecond clocks, samples and qualifies PP4 proximity
 * input, monitors PP3 motor-enable feedback, updates signed position from the
 * commanded direction, and detects a stopped prox stream.  It never performs
 * controller calculations, formatting or BDM output.
 */
void NEAR_FIXED timer_ch7_handler(void)
{
    unsigned long now_ms;
    unsigned char raw_state;

    TC7 = (unsigned short)(TC7 + TIMER_TICKS_1MS);
    TFLG1 = TC7_MASK;
    now_ms = ++Tick1msCount;

    ++Tick10msDivider;
    if (Tick10msDivider >= 10u) {
        Tick10msDivider = 0u;
        ++Tick10msCount;
    }

    /* PP4 is deliberately treated as ordinary GPIO, not as KWP4. */
    raw_state = ((PTP & PROX_INPUT_MASK) != 0u) ? 1u : 0u;
    ProxInputRaw = raw_state;
    MotorEnableFeedback =
        ((PTP & MOTOR_ENABLE_FEEDBACK_MASK) != 0u) ? 1u : 0u;

    /* Accept a change only after two consecutive 1 ms samples agree. */
    if (raw_state == ProxInputStable) {
        ProxCandidateState = raw_state;
        ProxQualifyCount = 0u;
    } else if (raw_state != ProxCandidateState) {
        ProxCandidateState = raw_state;
        ProxQualifyCount = 1u;
    } else {
        ++ProxQualifyCount;
        if (ProxQualifyCount >= PROX_QUALIFY_SAMPLES) {
            ProxInputStable = raw_state;
            ProxQualifyCount = 0u;

            /* Count and time rising edges only; duty-cycle asymmetry is ignored. */
            if (raw_state != 0u) {
                ++ProxEdgeCount;
                if (MotorActiveDirection > 0) {
                    ++MotionPositionCount;
                } else if (MotorActiveDirection < 0) {
                    --MotionPositionCount;
                }
                ProxLastRiseMs = now_ms;
                ProxStopped = 0u;
                if (ProxFirstRising != 0u) {
                    ProxFirstRising = 0u;
                } else {
                    ProxPeriodMs = now_ms - ProxPreviousRiseMs;
                    ProxPeriodValid = 1u;
                }
                ProxPreviousRiseMs = now_ms;
            }
        }
    }

    if ((ProxFirstRising == 0u) &&
        ((now_ms - ProxPreviousRiseMs) > PROX_STOP_TIMEOUT_MS)) {
        ProxStopped = 1u;
    }
}

/*
 * __premain
 * GCC runtime hook retained in fixed, nonpaged memory.  Startup calls it before
 * main; returning zero requests normal startup continuation.  No board setup
 * is performed here because main initializes the hardware explicitly.
 */
int __attribute__((near, section(".text.nonpaged"))) __premain(void)
{
    return 0;
}

/*
 * timer_init
 * Configure the free-running timer with a divide-by-32 prescaler, TC7 as the
 * 1 ms output-compare heartbeat, and PP4/PP3 as GPIO inputs.  TC7 is the only
 * timer channel and interrupt used by this proximity-feedback application.
 */
FILE_LOCAL void timer_init(void)
{
    /* PP3 reads the enable node; PP4 reads the prox signal. */
    DDRP &= (unsigned char)~(MOTOR_ENABLE_FEEDBACK_MASK | PROX_INPUT_MASK);
    PERP &= (unsigned char)~(MOTOR_ENABLE_FEEDBACK_MASK | PROX_INPUT_MASK);

    TIE = 0u;
    TSCR1 = TIMER_ENABLE;
    TSCR2 = (unsigned char)(TIMER_FAST_FLAG | TIMER_PRESCALE_32);

    TIOS |= TC7_MASK;

    TFLG1 = TC7_MASK;
    TC7 = (unsigned short)(TCNT + TIMER_TICKS_1MS);

    /* The 1 ms heartbeat polls and qualifies the PP4 prox input. */
    TIE = TC7_MASK;
}

/*
 * motor_force_safe
 * Immediately command both PWM legs to zero, remove the PA1 L6203 enable
 * command, clear the manual arm and direction, and publish status.  status is
 * zero for an ordinary stop, two for timeout, or three for rejected reversal.
 */
FILE_LOCAL void motor_force_safe(unsigned char status)
{
    /* Remove PWM first, then remove the PA1 enable command. */
    PWMDTY0 = 0u;
    PWMDTY1 = 0u;
    PORTA &= (unsigned char)~MOTOR_ENABLE_COMMAND_MASK;
    MotorOutputsEnabled = 0u;
    MotorTestArm = 0u;
    MotorTestStatus = status;
    MotorActiveDirection = 0;
}

/*
 * motor_pwm_init
 * Configure PWM0/PWM1 for independent, left-aligned 0..100 duty commands using
 * the established board clocking and polarity.  Both channels and PA1 are left
 * in the safe, disabled state after initialization.
 */
FILE_LOCAL void motor_pwm_init(void)
{
    /* Match the established ImageCraft configuration for PWM0/PWM1. */
    PWME &= (unsigned char)~(PWM0_MASK | PWM1_MASK);
    PWMPOL |= (unsigned char)(PWM0_MASK | PWM1_MASK);
    PWMCLK |= (unsigned char)(PWM0_MASK | PWM1_MASK);
    PWMPRCLK = (unsigned char)((PWMPRCLK & (unsigned char)~0x77u) | 0x11u);
    PWMCAE &= (unsigned char)~(PWM0_MASK | PWM1_MASK);
    PWMCTL &= (unsigned char)~0xF0u;
    PWMSCLA = 3u;
    PWMSCLB = 3u;
    PWMPER0 = 100u;
    PWMPER1 = 100u;
    PWMDTY0 = 0u;
    PWMDTY1 = 0u;
    PWMCNT0 = 0u;
    PWMCNT1 = 0u;
    PWME |= (unsigned char)(PWM0_MASK | PWM1_MASK);
    motor_force_safe(0u);
}

/*
 * motor_test_service
 * Apply the signed MotorTestDutyPercent command to the L6203 when MotorTestArm
 * contains MOTOR_ARM_VALUE.  Positive duty drives PWM0, negative duty drives
 * PWM1, and the opposite leg is always cleared first.  The service enforces a
 * bounded run time and requires a full stop/re-arm before direction reversal.
 * It is used by both manual bench commands and the automatic motion service.
 */
FILE_LOCAL void motor_test_service(void)
{
    signed char direction;
    unsigned char duty;
    unsigned long timeout_ms;

    if (MotorTestArm != MOTOR_ARM_VALUE) {
        if (MotorOutputsEnabled != 0u) {
            motor_force_safe(0u);
        }
        return;
    }

    if (MotorTestDutyPercent > 0) {
        direction = 1;
        duty = (unsigned char)MotorTestDutyPercent;
    } else if (MotorTestDutyPercent < 0) {
        direction = -1;
        duty = (unsigned char)(-MotorTestDutyPercent);
    } else {
        motor_force_safe(0u);
        return;
    }

    if (duty > 100u) {
        duty = 100u;
    }

    if (MotorOutputsEnabled == 0u) {
        MotorTestStartMs = Tick1msCount;
        MotorTestElapsedMs = 0ul;
        MotorActiveDirection = direction;
        MotorTestStatus = 1u;
        PORTA |= MOTOR_ENABLE_COMMAND_MASK;
        MotorOutputsEnabled = 1u;
    } else if (direction != MotorActiveDirection) {
        /* Require a complete stop/re-arm before reversing direction. */
        motor_force_safe(3u);
        return;
    }

    MotorTestElapsedMs = Tick1msCount - MotorTestStartMs;
    timeout_ms = MotorTestTimeoutMs;
    if ((timeout_ms == 0ul) || (timeout_ms > MOTOR_MAX_TIMEOUT_MS)) {
        timeout_ms = MOTOR_DEFAULT_TIMEOUT_MS;
    }
    if (MotorTestElapsedMs >= timeout_ms) {
        motor_force_safe(2u);
        return;
    }

    if (direction > 0) {
        PWMDTY1 = 0u;
        PWMDTY0 = duty;
    } else {
        PWMDTY0 = 0u;
        PWMDTY1 = duty;
    }
}

/*
 * motion_sequence_service
 * Bridge the portable motion state machine to DG128 feedback and motor globals.
 * A rising MOTION_ARM_VALUE starts a zero-referenced two-cycle test; removing
 * the arm cancels it.  Every new 10 ms tick converts prox period to signed speed
 * and calls MotionSequence_Step.  The function mirrors controller diagnostics
 * into NoICE-visible globals, queues CSV telemetry, and converts signed duty to
 * the guarded manual motor interface.  Call continuously from the main loop.
 */
FILE_LOCAL void motion_sequence_service(void)
{
    signed int measured_speed_x100;

    if ((CoatAutomaticActive != 0u) &&
        (MotionTestArm == MOTION_ARM_VALUE)) {
        /* The coating and legacy automatic tests may not own the motor together. */
        MotionTestArm = 0u;
    }

    if ((MotionTestArm == MOTION_ARM_VALUE) &&
        (MotionPreviousArm != MOTION_ARM_VALUE) &&
        (CoatAutomaticActive == 0u)) {
        MotionPositionCount = 0l;
        prox_speed_invalidate();
        MotionSequence_Start(&MotionSequence, Tick1msCount, MotionPositionCount);
        MotionAutomaticActive = 1u;
        MotionNextTelemetryMs = Tick1msCount;
        MotionFinalTelemetrySent = 0u;
        NoICE_VuartWrite(MotionCsv_Header());
    } else if ((MotionTestArm != MOTION_ARM_VALUE) &&
               (MotionPreviousArm == MOTION_ARM_VALUE) &&
        (MotionAutomaticActive != 0u)) {
        MotionSequence_Stop(&MotionSequence);
        MotionAutomaticActive = 0u;
        MotorTestDutyPercent = 0;
        MotorTestArm = 0u;
    }
    MotionPreviousArm = MotionTestArm;

    if ((MotionAutomaticActive != 0u) &&
        (Tick10msCount != MotionLastControlTick)) {
        MotionLastControlTick = Tick10msCount;
        measured_speed_x100 = 0;
        if ((ProxPeriodValid != 0u) && (ProxStopped == 0u) &&
            (ProxPeriodMs != 0ul)) {
            measured_speed_x100 =
                (signed int)(100000ul / ProxPeriodMs);
            if (MotorActiveDirection < 0) {
                measured_speed_x100 = (signed int)-measured_speed_x100;
            } else if (MotorActiveDirection == 0) {
                measured_speed_x100 = 0;
            }
        }
        MotionSequence_Step(&MotionSequence, Tick1msCount,
                            MotionPositionCount, measured_speed_x100);
    }

    MotionState = MotionSequence.state;
    MotionCycle = MotionSequence.cycle;
    MotionFault = MotionSequence.fault;
    MotionTargetCount = MotionSequence.target_counts;
    MotionCommandDuty = MotionSequence.duty_command;
    MotionPositionErrorCounts = MotionSequence.position_error_counts;
    MotionSpeedCommandX100 = MotionSequence.speed_command_x100;
    MotionMeasuredSpeedX100 = MotionSequence.measured_speed_x100;
    MotionSpeedErrorX100 = MotionSequence.speed_error_x100;
    MotionSpeedIntegralX100 = MotionSequence.speed_integral_x100;

    if ((MotionAutomaticActive != 0u) &&
        (Tick1msCount >= MotionNextTelemetryMs)) {
        MotionCsv_Format(MotionTelemetryLine, sizeof(MotionTelemetryLine),
                         Tick1msCount, &MotionSequence,
                         MotionPositionCount, NoICE_VuartDroppedRecords);
        NoICE_VuartWrite(MotionTelemetryLine);
        MotionNextTelemetryMs += MOTION_TELEMETRY_PERIOD_MS;
    }

    if ((MotionAutomaticActive != 0u) &&
        (MotionFinalTelemetrySent == 0u) &&
        ((MotionSequence.state == MOTION_COMPLETE) ||
         (MotionSequence.state == MOTION_FAULT))) {
        MotionCsv_Format(MotionTelemetryLine, sizeof(MotionTelemetryLine),
                         Tick1msCount, &MotionSequence,
                         MotionPositionCount, NoICE_VuartDroppedRecords);
        NoICE_VuartWrite(MotionTelemetryLine);
        MotionFinalTelemetrySent = 1u;
    }

    if ((MotionAutomaticActive != 0u) &&
        ((MotionSequence.state == MOTION_COMPLETE) ||
         (MotionSequence.state == MOTION_FAULT))) {
        MotionTestArm = 0u;
        MotorTestDutyPercent = 0;
        MotorTestArm = 0u;
        MotionAutomaticActive = 0u;
        MotionPreviousArm = 0u;
    } else if ((MotionAutomaticActive != 0u) &&
               (MotionSequence.duty_command == 0)) {
        MotorTestDutyPercent = 0;
        MotorTestArm = 0u;
    } else if (MotionAutomaticActive != 0u) {
        MotorTestDutyPercent = MotionSequence.duty_command;
        MotorTestTimeoutMs = MOTOR_MAX_TIMEOUT_MS;
        MotorTestArm = MOTOR_ARM_VALUE;
    }
}

/* Return signed proximity speed in counts/second x100. */
FILE_LOCAL signed int coating_measured_speed(void)
{
    signed int speed_x100;

    speed_x100 = 0;
    if ((ProxPeriodValid != 0u) && (ProxStopped == 0u) &&
        (ProxPeriodMs != 0ul)) {
        speed_x100 = (signed int)(100000ul / ProxPeriodMs);
        if (MotorActiveDirection < 0) {
            speed_x100 = (signed int)-speed_x100;
        } else if (MotorActiveDirection == 0) {
            speed_x100 = 0;
        }
    }
    return speed_x100;
}

/* Convert a CAN position byte in tenths of an inch to rounded prox counts. */
FILE_LOCAL signed long coating_tenths_to_counts(unsigned char tenths)
{
    unsigned long scaled;

    scaled = (unsigned long)tenths *
             (unsigned long)EmbeddedCoatingSettings.feedback_counts_per_inch_x100;
    return (signed long)((scaled + 500ul) / 1000ul);
}

/* Convert the CAN speed-percent byte into prox counts/second x100. */
FILE_LOCAL signed int coating_percent_to_speed(unsigned char percent)
{
    unsigned long scaled;

    scaled = (unsigned long)percent *
             (unsigned long)EmbeddedCoatingSettings.motor_max_speed_counts_x100;
    return (signed int)((scaled + 50ul) / 100ul);
}

/* Copy editable NoICE menu globals into the portable validated settings. */
FILE_LOCAL void coating_load_settings(void)
{
    EmbeddedCoatingSettings.actuator_length_tenths = CoatActuatorLengthTenths;
    EmbeddedCoatingSettings.short_stroke_count = CoatShortStrokeCount;
    EmbeddedCoatingSettings.short_length_tenths = CoatShortLengthTenths;
    EmbeddedCoatingSettings.long_stroke_count = CoatLongStrokeCount;
    EmbeddedCoatingSettings.long_length_tenths = CoatLongLengthTenths;
    EmbeddedCoatingSettings.positioning_speed_percent =
        CoatPositioningSpeedPercent;
    EmbeddedCoatingSettings.homing_speed_percent = CoatHomingSpeedPercent;
    EmbeddedCoatingSettings.fast_stroke_count = CoatFastStrokeCount;
    EmbeddedCoatingSettings.short_fast_speed_percent =
        CoatShortFastSpeedPercent;
    EmbeddedCoatingSettings.short_slow_speed_percent =
        CoatShortSlowSpeedPercent;
    EmbeddedCoatingSettings.long_fast_speed_percent =
        CoatLongFastSpeedPercent;
    EmbeddedCoatingSettings.long_slow_speed_percent =
        CoatLongSlowSpeedPercent;
    EmbeddedCoatingSettings.feedback_counts_per_inch_x100 =
        CoatFeedbackCountsPerInchX100;
    EmbeddedCoatingSettings.motor_max_speed_counts_x100 =
        CoatMotorMaxSpeedCountsX100;
    CoatingSettings_Validate(&EmbeddedCoatingSettings);

    /* Publish any validation/clamping so the menu and active values agree. */
    CoatActuatorLengthTenths =
        EmbeddedCoatingSettings.actuator_length_tenths;
    CoatShortLengthTenths = EmbeddedCoatingSettings.short_length_tenths;
    CoatLongLengthTenths = EmbeddedCoatingSettings.long_length_tenths;
    CoatPositioningSpeedPercent =
        EmbeddedCoatingSettings.positioning_speed_percent;
    CoatHomingSpeedPercent = EmbeddedCoatingSettings.homing_speed_percent;
    CoatShortFastSpeedPercent =
        EmbeddedCoatingSettings.short_fast_speed_percent;
    CoatShortSlowSpeedPercent =
        EmbeddedCoatingSettings.short_slow_speed_percent;
    CoatLongFastSpeedPercent =
        EmbeddedCoatingSettings.long_fast_speed_percent;
    CoatLongSlowSpeedPercent =
        EmbeddedCoatingSettings.long_slow_speed_percent;
    CoatFeedbackCountsPerInchX100 =
        EmbeddedCoatingSettings.feedback_counts_per_inch_x100;
    CoatMotorMaxSpeedCountsX100 =
        EmbeddedCoatingSettings.motor_max_speed_counts_x100;
}

/* Mirror the portable structures into flat NoICE-friendly scalar globals. */
FILE_LOCAL void coating_publish_diagnostics(void)
{
    CoatOperation = EmbeddedCoatingCycle.operation;
    CoatStrokeNumber = EmbeddedCoatingCycle.stroke_number;
    CoatStrokeTotal = EmbeddedCoatingCycle.stroke_total;
    CoatDirectionExtend = EmbeddedCoatingCycle.direction_extend;
    CoatTargetTenths = EmbeddedCoatingCycle.target_tenths;
    CoatSpeedPercent = EmbeddedCoatingCycle.speed_percent;

    MotionState = MotionSequence.state;
    MotionCycle = MotionSequence.cycle;
    MotionFault = MotionSequence.fault;
    MotionTargetCount = MotionSequence.target_counts;
    MotionCommandDuty = MotionSequence.duty_command;
    MotionPositionErrorCounts = MotionSequence.position_error_counts;
    MotionSpeedCommandX100 = MotionSequence.speed_command_x100;
    MotionMeasuredSpeedX100 = MotionSequence.measured_speed_x100;
    MotionSpeedErrorX100 = MotionSequence.speed_error_x100;
    MotionSpeedIntegralX100 = MotionSequence.speed_integral_x100;
}

/* Queue one event-oriented coating record to the nonblocking Virtual UART. */
FILE_LOCAL void coating_emit_telemetry(void)
{
    CoatingCsv_Format(CoatingTelemetryLine, sizeof(CoatingTelemetryLine),
                      Tick1msCount, &EmbeddedCoatingCycle, &MotionSequence,
                      SimCanMoving, MotionPositionCount,
                      NoICE_VuartDroppedRecords);
    NoICE_VuartWrite(CoatingTelemetryLine);
}

/* Process one pending two-byte command exactly where real CAN mapping will fit. */
FILE_LOCAL void simulated_can_receive_service(void)
{
    signed long target_counts;
    signed int speed_x100;

    if (SimCanCommandPending == 0u) {
        return;
    }
    SimCanCommandPending = 0u;

    if ((SimCanPositionTenths == SimCanPreviousPosition) &&
        (SimCanSpeedPercent == SimCanPreviousSpeed)) {
        SimCanFault = 3u;
        CoatingCycle_SetFault(&EmbeddedCoatingCycle, SimCanFault);
        return;
    }
    SimCanPreviousPosition = SimCanPositionTenths;
    SimCanPreviousSpeed = SimCanSpeedPercent;

    if (SimCanSpeedPercent == 0u) {
        MotionSequence_Stop(&MotionSequence);
        SimCanMoving = 0u;
        return;
    }

    target_counts = coating_tenths_to_counts(SimCanPositionTenths);
    speed_x100 = coating_percent_to_speed(SimCanSpeedPercent);
    prox_speed_invalidate();
    MotionMove_Start(&MotionSequence, Tick1msCount, MotionPositionCount,
                     target_counts, speed_x100);
    SimCanMoving = (MotionSequence.state == MOTION_COMPLETE) ? 0u : 1u;
    coating_publish_diagnostics();
    coating_emit_telemetry();
}

/*
 * coating_test_service
 * Run the embedded coating application using simulated CAN process-image
 * bytes and real PP4/motor feedback. Arm with hexadecimal D4 in NoICE. The
 * home phase deliberately does not drive the bench motor; after the configured
 * delay it establishes the current location as count zero.
 */
FILE_LOCAL void coating_test_service(void)
{
    signed int measured_speed_x100;
    unsigned char command_position;
    unsigned char command_speed;
    unsigned long home_delay;

    if ((CoatingTestArm == COATING_ARM_VALUE) &&
        (CoatingPreviousArm != COATING_ARM_VALUE)) {
        if (MotionAutomaticActive != 0u) {
            CoatingTestArm = 0u;
            SimCanFault = 4u;
        } else {
            coating_load_settings();
            MotionSequence_Stop(&MotionSequence);
            CoatingCycle_Start(&EmbeddedCoatingCycle,
                               &EmbeddedCoatingSettings);
            SimCanPreviousPosition = 255u;
            SimCanPreviousSpeed = 255u;
            SimCanPositionTenths = 0u;
            SimCanSpeedPercent = 0u;
            SimCanCommandPending = 0u;
            SimCanMoving = 1u;
            SimCanFault = 0u;
            CoatAutomaticActive = 1u;
            CoatingHomeStartMs = Tick1msCount;
            CoatingNextCommandMs = Tick1msCount;
            MotorTestDutyPercent = 0;
            MotorTestArm = 0u;
            NoICE_VuartWrite(CoatingCsv_Header());
            coating_publish_diagnostics();
            coating_emit_telemetry();
        }
    } else if ((CoatingTestArm != COATING_ARM_VALUE) &&
               (CoatingPreviousArm == COATING_ARM_VALUE) &&
               (CoatAutomaticActive != 0u)) {
        MotionSequence_Stop(&MotionSequence);
        CoatingCycle_SetFault(&EmbeddedCoatingCycle, 5u);
        SimCanMoving = 0u;
        SimCanFault = 5u;
        CoatAutomaticActive = 0u;
        MotorTestDutyPercent = 0;
        MotorTestArm = 0u;
        coating_publish_diagnostics();
        coating_emit_telemetry();
    }
    CoatingPreviousArm = CoatingTestArm;

    if (CoatAutomaticActive == 0u) {
        coating_publish_diagnostics();
        return;
    }

    if (EmbeddedCoatingCycle.operation == COAT_HOME) {
        home_delay = CoatSimHomeDelayMs;
        if (home_delay > MOTOR_MAX_TIMEOUT_MS) {
            home_delay = COATING_DEFAULT_HOME_DELAY_MS;
        }
        if ((Tick1msCount - CoatingHomeStartMs) >= home_delay) {
            MotionPositionCount = 0l;
            SimCanMoving = 0u;
            CoatingCycle_HomeComplete(&EmbeddedCoatingCycle,
                                      &EmbeddedCoatingSettings);
            CoatingNextCommandMs = Tick1msCount + COATING_COMMAND_GAP_MS;
            coating_publish_diagnostics();
            coating_emit_telemetry();
        }
    }

    if (Tick10msCount != CoatingLastControlTick) {
        CoatingLastControlTick = Tick10msCount;
        measured_speed_x100 = coating_measured_speed();

        if (SimCanMoving != 0u &&
            EmbeddedCoatingCycle.operation != COAT_HOME) {
            MotionMove_Step(&MotionSequence, Tick1msCount,
                            MotionPositionCount, measured_speed_x100);
            if (MotionSequence.state == MOTION_COMPLETE) {
                SimCanMoving = 0u;
                coating_publish_diagnostics();
                coating_emit_telemetry();
                CoatingCycle_MoveComplete(&EmbeddedCoatingCycle,
                                          &EmbeddedCoatingSettings);
                CoatingNextCommandMs =
                    Tick1msCount + COATING_COMMAND_GAP_MS;
            } else if (MotionSequence.state == MOTION_FAULT) {
                SimCanMoving = 0u;
                SimCanFault = MotionSequence.fault;
                CoatingCycle_SetFault(&EmbeddedCoatingCycle, SimCanFault);
            }
        }

        if ((SimCanMoving == 0u) &&
            (Tick1msCount >= CoatingNextCommandMs) &&
            CoatingCycle_TakeCommand(&EmbeddedCoatingCycle,
                                     &command_position, &command_speed)) {
            SimCanPositionTenths = command_position;
            SimCanSpeedPercent = command_speed;
            SimCanCommandPending = 1u;
            simulated_can_receive_service();
            if (SimCanMoving == 0u && SimCanFault == 0u) {
                CoatingCycle_MoveComplete(&EmbeddedCoatingCycle,
                                          &EmbeddedCoatingSettings);
                CoatingNextCommandMs =
                    Tick1msCount + COATING_COMMAND_GAP_MS;
            }
        }
    }

    coating_publish_diagnostics();

    if ((EmbeddedCoatingCycle.operation == COAT_COMPLETE) ||
        (EmbeddedCoatingCycle.operation == COAT_FAULT)) {
        SimCanMoving = 0u;
        if (EmbeddedCoatingCycle.operation == COAT_FAULT) {
            SimCanFault = EmbeddedCoatingCycle.fault;
        }
        MotorTestDutyPercent = 0;
        MotorTestArm = 0u;
        CoatAutomaticActive = 0u;
        CoatingTestArm = 0u;
        CoatingPreviousArm = 0u;
        coating_publish_diagnostics();
        coating_emit_telemetry();
    } else if (MotionSequence.duty_command == 0) {
        MotorTestDutyPercent = 0;
        MotorTestArm = 0u;
    } else {
        MotorTestDutyPercent = MotionSequence.duty_command;
        MotorTestTimeoutMs = MOTOR_MAX_TIMEOUT_MS;
        MotorTestArm = MOTOR_ARM_VALUE;
    }
}

/*
 * main
 * Establish safe GPIO levels, initialize clock/PWM/timer/controller/Virtual
 * UART services, enable interrupts, and run the cooperative foreground loop.
 * Interrupts acquire time and feedback; the foreground performs control,
 * motor command arbitration and nonblocking telemetry indefinitely.
 */
int main(void)
{
    /* PA1 commands ENABLE through R1/C4. Start with it safely low. */
    PORTA &= (unsigned char)~MOTOR_ENABLE_COMMAND_MASK;
    DDRA |= MOTOR_ENABLE_COMMAND_MASK;

    /* PWM owns PP0/PP1. PP3 enable feedback and PP4 prox remain inputs. */
    DDRP &= (unsigned char)~(MOTOR_ENABLE_FEEDBACK_MASK | PROX_INPUT_MASK);
    PERP &= (unsigned char)~(MOTOR_ENABLE_FEEDBACK_MASK | PROX_INPUT_MASK);
    MotorOutputsEnabled = 0u;

    pll_init();
    motor_pwm_init();
    timer_init();
    MotionSequence_Init(&MotionSequence);
    CoatingSettings_Default(&EmbeddedCoatingSettings);
    CoatingCycle_Init(&EmbeddedCoatingCycle);
    NoICE_VuartInit();
    NoICE_VuartWrite(MotionCsv_Header());
    StartupPassed = 0x5Au;

    __asm__ __volatile__("cli");

    for (;;) {
        NoICE_VuartService();
        motion_sequence_service();
        coating_test_service();
        motor_test_service();
        NoICE_VuartService();
        ++MainLoopCount;
    }
}
