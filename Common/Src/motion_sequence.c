#include "motion_sequence.h"
#include "debug_visibility.h"

/* Motion profile used by both the PC simulation and the embedded target. */
#define OUTWARD_TARGET_COUNTS 49l  /* Proximity rising edges from retracted. */
#define TEST_CYCLES 2u            /* One cycle is extend, pause and retract. */
#define MAX_DUTY_PERCENT 95       /* Absolute PWM command ceiling. */
#define MIN_DUTY_PERCENT 10       /* Minimum useful command while moving. */
#define REVERSAL_PAUSE_MS 100ul   /* Motor-off time before reversing. */
#define MOVE_TIMEOUT_MS 45000ul   /* Independent timeout for each direction. */

/*
 * Fixed-point cascaded position/speed controller.
 *
 * The outer proportional loop converts position error, in proximity counts,
 * into a requested speed.  POSITION_KP_X100 is requested counts/second x100
 * per count of position error.  A value of 250 therefore requests 2.50
 * counts/second for each count of error, subject to MAX_SPEED_X100.
 *
 * The inner PI loop converts speed error into PWM duty.  Speed quantities use
 * counts/second x100.  Duty, feed-forward output and the integral use percent
 * x100, allowing fractional-percent calculations without floating point.
 * MAX_DUTY_PERCENT is only a safety/output ceiling; the feed-forward and PI
 * gains determine the duty normally requested below that ceiling.
 */
#define POSITION_KP_X100 250      /* 2.50 count/s per count of error. */
#define MAX_SPEED_X100 300        /* Maximum command is 3.00 counts/s. */
#define DUTY_FEEDFORWARD_GAIN 1667 /* 3.00 count/s produces about 50% duty. */
#define SPEED_KP_GAIN 10          /* Tested proportional duty correction. */
#define SPEED_KI_STEP_GAIN 10     /* Tested integral correction per update. */
#define INTEGRAL_LIMIT_X100 2500  /* Limit integral contribution to +/-25%. */

/*
 * ControllerReset
 * Clear all controller diagnostics and the accumulated speed integral.
 * Call whenever a move stops or changes phase so old PI error cannot affect
 * the next direction.  sequence must point to a valid MOTION_SEQUENCE.
 */
FILE_LOCAL void ControllerReset(MOTION_SEQUENCE *sequence)
{
    /* Prevent a previous move or direction from carrying PI history forward. */
    sequence->position_error_counts = 0;
    sequence->speed_command_x100 = 0;
    sequence->measured_speed_x100 = 0;
    sequence->speed_error_x100 = 0;
    sequence->speed_integral_x100 = 0;
}

/*
 * ControllerStep
 * Execute one position-P/speed-PI update and return signed PWM percent.
 * position_error is target minus feedback in prox counts; measured_speed_x100
 * is signed prox counts/second x100.  The function also updates the diagnostic
 * fields in sequence.  It does not access hardware or retain hidden state.
 */
FILE_LOCAL signed char ControllerStep(MOTION_SEQUENCE *sequence,
                                  signed long position_error,
                                  signed int measured_speed_x100)
{
    signed long speed_command;
    signed long duty_x100;
    signed long integral;
    signed char direction;

    /* Retain a signed 16-bit diagnostic copy without allowing overflow. */
    if (position_error > 32767l) {
        sequence->position_error_counts = 32767;
    } else if (position_error < -32767l) {
        sequence->position_error_counts = -32767;
    } else {
        sequence->position_error_counts = (signed int)position_error;
    }

    /* Outer position loop followed by the configured speed limit. */
    speed_command = position_error * POSITION_KP_X100;
    if (speed_command > sequence->speed_limit_x100) {
        speed_command = sequence->speed_limit_x100;
    } else if (speed_command < -sequence->speed_limit_x100) {
        speed_command = -sequence->speed_limit_x100;
    }
    sequence->speed_command_x100 = (signed int)speed_command;
    sequence->measured_speed_x100 = measured_speed_x100;
    sequence->speed_error_x100 =
        (signed int)(sequence->speed_command_x100 - measured_speed_x100);

    /* Inner speed PI loop.  Integral limiting provides basic anti-windup. */
    integral = sequence->speed_integral_x100;
    integral += ((signed long)sequence->speed_error_x100 *
                 SPEED_KI_STEP_GAIN) / 100l;
    if (integral > INTEGRAL_LIMIT_X100) {
        integral = INTEGRAL_LIMIT_X100;
    } else if (integral < -INTEGRAL_LIMIT_X100) {
        integral = -INTEGRAL_LIMIT_X100;
    }
    sequence->speed_integral_x100 = (signed int)integral;

    /* Feed-forward supplies nominal motor drive; PI corrects speed error. */
    duty_x100 = ((speed_command * DUTY_FEEDFORWARD_GAIN) / 100l) +
                ((signed long)sequence->speed_error_x100 * SPEED_KP_GAIN) +
                integral;

    /* Apply minimum useful drive and the absolute PWM ceiling by direction. */
    direction = (position_error > 0l) ? 1 : -1;
    if (direction > 0) {
        if (duty_x100 < (MIN_DUTY_PERCENT * 100l)) {
            duty_x100 = MIN_DUTY_PERCENT * 100l;
        } else if (duty_x100 > (MAX_DUTY_PERCENT * 100l)) {
            duty_x100 = MAX_DUTY_PERCENT * 100l;
        }
    } else {
        if (duty_x100 > -(MIN_DUTY_PERCENT * 100l)) {
            duty_x100 = -(MIN_DUTY_PERCENT * 100l);
        } else if (duty_x100 < -(MAX_DUTY_PERCENT * 100l)) {
            duty_x100 = -(MAX_DUTY_PERCENT * 100l);
        }
    }

    return (signed char)(duty_x100 / 100l);
}

/*
 * MotionSequence_Init
 * Put a sequence object into the safe idle state and install the configured
 * cycle count.  This initializes software only and never starts the motor.
 */
void MotionSequence_Init(MOTION_SEQUENCE *sequence)
{
    /* Initialization is motor-safe and does not start a sequence. */
    sequence->state = MOTION_IDLE;
    sequence->cycle = 0u;
    sequence->total_cycles = TEST_CYCLES;
    sequence->fault = 0u;
    sequence->target_counts = 0l;
    sequence->duty_command = 0;
    sequence->speed_limit_x100 = MAX_SPEED_X100;
    sequence->state_start_ms = 0ul;
    ControllerReset(sequence);
}

/*
 * MotionSequence_Start
 * Begin the first outward stroke at now_ms.  The bench application establishes
 * the retracted position as zero before calling this function.  The initial
 * duty is provisional; MotionSequence_Step calculates subsequent commands.
 */
void MotionSequence_Start(MOTION_SEQUENCE *sequence,
                          unsigned long now_ms,
                          signed long current_position)
{
    /*
     * The bench test defines its starting point as position zero.  The caller
     * is responsible for establishing that reference before arming the move.
     */
    (void)current_position;
    sequence->state = MOTION_EXTENDING;
    sequence->cycle = 1u;
    sequence->fault = 0u;
    sequence->target_counts = OUTWARD_TARGET_COUNTS;
    sequence->speed_limit_x100 = MAX_SPEED_X100;
    sequence->duty_command = MAX_DUTY_PERCENT;
    sequence->state_start_ms = now_ms;
    ControllerReset(sequence);
}

/*
 * MotionSequence_Stop
 * Cancel an active sequence, command zero duty and clear the controller.
 * The platform layer is still responsible for applying zero to the hardware.
 */
void MotionSequence_Stop(MOTION_SEQUENCE *sequence)
{
    /* A stop cancels the sequence and removes the commanded motor duty. */
    sequence->state = MOTION_IDLE;
    sequence->duty_command = 0;
    ControllerReset(sequence);
}

/*
 * MotionMove_Start
 * Start one absolute position move. target_position and current_position use
 * proximity counts. speed_limit_x100 is a positive counts/second x100 limit.
 * A target already reached completes immediately without commanding PWM.
 */
void MotionMove_Start(MOTION_SEQUENCE *sequence,
                      unsigned long now_ms,
                      signed long current_position,
                      signed long target_position,
                      signed int speed_limit_x100)
{
    if (speed_limit_x100 < 0) {
        speed_limit_x100 = (signed int)-speed_limit_x100;
    }
    if (speed_limit_x100 == 0) {
        speed_limit_x100 = 1;
    }

    sequence->cycle = 0u;
    sequence->total_cycles = 0u;
    sequence->fault = 0u;
    sequence->target_counts = target_position;
    sequence->speed_limit_x100 = speed_limit_x100;
    sequence->duty_command = 0;
    sequence->state_start_ms = now_ms;
    ControllerReset(sequence);

    if (target_position > current_position) {
        sequence->state = MOTION_EXTENDING;
    } else if (target_position < current_position) {
        sequence->state = MOTION_RETRACTING;
    } else {
        sequence->state = MOTION_COMPLETE;
    }
}

/*
 * MotionMove_Step
 * Execute one update of a single point-to-point move. Completion occurs when
 * feedback reaches or passes the target; the controller stops rather than
 * reversing to correct an overshoot. The caller owns the moving status flag.
 */
void MotionMove_Step(MOTION_SEQUENCE *sequence,
                     unsigned long now_ms,
                     signed long current_position,
                     signed int measured_speed_x100)
{
    signed long remaining;

    if ((sequence->state != MOTION_EXTENDING) &&
        (sequence->state != MOTION_RETRACTING)) {
        sequence->duty_command = 0;
        return;
    }

    if ((now_ms - sequence->state_start_ms) > MOVE_TIMEOUT_MS) {
        sequence->fault = (sequence->state == MOTION_EXTENDING) ? 1u : 2u;
        sequence->state = MOTION_FAULT;
        sequence->duty_command = 0;
        ControllerReset(sequence);
        return;
    }

    remaining = sequence->target_counts - current_position;
    if (((sequence->state == MOTION_EXTENDING) && (remaining <= 0l)) ||
        ((sequence->state == MOTION_RETRACTING) && (remaining >= 0l))) {
        sequence->state = MOTION_COMPLETE;
        sequence->duty_command = 0;
        ControllerReset(sequence);
        return;
    }

    sequence->duty_command =
        ControllerStep(sequence, remaining, measured_speed_x100);
}

/*
 * MotionSequence_Step
 * Advance the motion state machine and controller by one 10 ms service step.
 * now_ms is the monotonic platform time, current_position is the signed prox
 * count, and measured_speed_x100 is signed counts/second x100.  The resulting
 * state and duty_command are returned through sequence; no hardware is driven
 * directly.  A move timeout sets state MOTION_FAULT and a direction-specific
 * fault code.
 */
void MotionSequence_Step(MOTION_SEQUENCE *sequence,
                         unsigned long now_ms,
                         signed long current_position,
                         signed int measured_speed_x100)
{
    signed long remaining;

    switch (sequence->state) {
    case MOTION_EXTENDING:
        /* Fault if feedback cannot reach the outward target in time. */
        if ((now_ms - sequence->state_start_ms) > MOVE_TIMEOUT_MS) {
            sequence->state = MOTION_FAULT;
            sequence->fault = 1u;
            sequence->duty_command = 0;
            ControllerReset(sequence);
            break;
        }
        remaining = sequence->target_counts - current_position;
        if (remaining <= 0l) {
            /* Reaching or passing the target stops drive; do not reverse. */
            sequence->state = MOTION_PAUSE_EXTEND;
            sequence->duty_command = 0;
            sequence->state_start_ms = now_ms;
            ControllerReset(sequence);
        } else {
            sequence->duty_command =
                ControllerStep(sequence, remaining, measured_speed_x100);
        }
        break;

    case MOTION_PAUSE_EXTEND:
        /* Hold zero duty long enough for the bridge and motor to settle. */
        sequence->duty_command = 0;
        ControllerReset(sequence);
        if ((now_ms - sequence->state_start_ms) >= REVERSAL_PAUSE_MS) {
            sequence->state = MOTION_RETRACTING;
            sequence->target_counts = 0l;
            sequence->state_start_ms = now_ms;
        }
        break;

    case MOTION_RETRACTING:
        /* Retraction uses the same controller with a negative position error. */
        if ((now_ms - sequence->state_start_ms) > MOVE_TIMEOUT_MS) {
            sequence->state = MOTION_FAULT;
            sequence->fault = 2u;
            sequence->duty_command = 0;
            ControllerReset(sequence);
            break;
        }
        remaining = current_position - sequence->target_counts;
        if (remaining <= 0l) {
            sequence->state = MOTION_PAUSE_RETRACT;
            sequence->duty_command = 0;
            sequence->state_start_ms = now_ms;
            ControllerReset(sequence);
        } else {
            sequence->duty_command =
                ControllerStep(sequence, -remaining, measured_speed_x100);
        }
        break;

    case MOTION_PAUSE_RETRACT:
        /* Finish after the requested cycles or begin the next extension. */
        sequence->duty_command = 0;
        ControllerReset(sequence);
        if ((now_ms - sequence->state_start_ms) >= REVERSAL_PAUSE_MS) {
            if (sequence->cycle >= sequence->total_cycles) {
                sequence->state = MOTION_COMPLETE;
            } else {
                ++sequence->cycle;
                sequence->state = MOTION_EXTENDING;
                sequence->target_counts = OUTWARD_TARGET_COUNTS;
                sequence->state_start_ms = now_ms;
            }
        }
        break;

    case MOTION_COMPLETE:
    case MOTION_FAULT:
    case MOTION_IDLE:
    default:
        sequence->duty_command = 0;
        ControllerReset(sequence);
        break;
    }
}
