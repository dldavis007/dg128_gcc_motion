#include <stdio.h>
#include <string.h>
#include "motion_sequence.h"
#include "coating_cycle.h"

#define PULSES_PER_REV 9.0
#define MOTOR_MAX_RPM 40.0
#define SIM_STEP_MS 1ul
#define MOTOR_TIME_CONSTANT_MS 180.0
#define PROX_STOP_TIMEOUT_MS 3000ul
#define SIM_TIMEOUT_MS 180000ul
#define CAN_COMMAND_GAP_MS 100ul

typedef struct
{
    unsigned char position_tenths;
    unsigned char speed_percent;
    unsigned char moving;
    unsigned char fault;
    unsigned char previous_position_tenths;
    unsigned char previous_speed_percent;
} CAN_PROCESS_IMAGE;

static const char *OperationName(unsigned char operation)
{
    switch (operation) {
    case COAT_HOME: return "HOME";
    case COAT_POSITION_START: return "POSITION_START";
    case COAT_SHORT_STROKE: return "SHORT_STROKE";
    case COAT_LONG_STROKE: return "LONG_STROKE";
    case COAT_COMPLETE: return "COMPLETE";
    case COAT_FAULT: return "FAULT";
    default: return "IDLE";
    }
}

static signed long TenthsToCounts(unsigned char tenths,
                                  unsigned int counts_per_inch_x100)
{
    unsigned long scaled;

    scaled = (unsigned long)tenths * (unsigned long)counts_per_inch_x100;
    return (signed long)((scaled + 500ul) / 1000ul);
}

static signed int PercentToSpeedX100(unsigned char percent,
                                    unsigned int maximum_speed_x100)
{
    unsigned long scaled;

    scaled = (unsigned long)percent * (unsigned long)maximum_speed_x100;
    return (signed int)((scaled + 50ul) / 100ul);
}

static unsigned char CanReceiveMove(CAN_PROCESS_IMAGE *can,
                                    MOTION_SEQUENCE *motion,
                                    const COATING_SETTINGS *settings,
                                    unsigned long now_ms,
                                    signed long current_position,
                                    unsigned char position_tenths,
                                    unsigned char speed_percent)
{
    signed long target_counts;
    signed int speed_x100;

    if ((position_tenths == can->previous_position_tenths) &&
        (speed_percent == can->previous_speed_percent)) {
        return 0u;
    }

    can->position_tenths = position_tenths;
    can->speed_percent = speed_percent;
    can->previous_position_tenths = position_tenths;
    can->previous_speed_percent = speed_percent;
    can->fault = 0u;
    target_counts = TenthsToCounts(position_tenths,
                                   settings->feedback_counts_per_inch_x100);
    speed_x100 = PercentToSpeedX100(speed_percent,
                                    settings->motor_max_speed_counts_x100);
    MotionMove_Start(motion, now_ms, current_position,
                     target_counts, speed_x100);
    can->moving = (motion->state == MOTION_COMPLETE) ? 0u : 1u;
    return 1u;
}

static void PrintSettings(const COATING_SETTINGS *settings)
{
    printf("Menu settings:\n");
    printf("  actuator_length       = %u.%u in\n",
           settings->actuator_length_tenths / 10u,
           settings->actuator_length_tenths % 10u);
    printf("  short_strokes         = %u at %u.%u in\n",
           settings->short_stroke_count,
           settings->short_length_tenths / 10u,
           settings->short_length_tenths % 10u);
    printf("  long_strokes          = %u at %u.%u in\n",
           settings->long_stroke_count,
           settings->long_length_tenths / 10u,
           settings->long_length_tenths % 10u);
    printf("  first %u strokes/group use fast speed\n",
           settings->fast_stroke_count);
    printf("  short speed fast/slow = %u/%u%%\n",
           settings->short_fast_speed_percent,
           settings->short_slow_speed_percent);
    printf("  long speed fast/slow  = %u/%u%%\n",
           settings->long_fast_speed_percent,
           settings->long_slow_speed_percent);
    printf("  feedback resolution   = %.2f counts/in\n",
           (double)settings->feedback_counts_per_inch_x100 / 100.0);
}

int main(int argc, char **argv)
{
    COATING_SETTINGS settings;
    COATING_CYCLE coating;
    MOTION_SEQUENCE motion;
    CAN_PROCESS_IMAGE can;
    unsigned long now_ms;
    unsigned long next_control_ms;
    unsigned long next_report_ms;
    signed long position;
    double pulse_accumulator;
    double demanded_rpm;
    double actual_rpm;
    unsigned long last_pulse_ms;
    unsigned long pulse_period_ms;
    unsigned char pulse_period_valid;
    signed int measured_speed_x100;
    unsigned char command_position;
    unsigned char command_speed;
    unsigned char previous_moving;
    unsigned char previous_motion_state;
    unsigned char home_active;
    unsigned char last_stroke_direction;
    unsigned char transition_reversal_ok;
    unsigned char saw_short;
    unsigned char saw_long;
    unsigned long next_command_ms;
    FILE *csv;

    CoatingSettings_Default(&settings);
    if ((argc > 1) && (strcmp(argv[1], "short-zero") == 0)) {
        settings.short_stroke_count = 0u;
    } else if ((argc > 1) && (strcmp(argv[1], "long-zero") == 0)) {
        settings.long_stroke_count = 0u;
    } else if ((argc > 1) && (strcmp(argv[1], "both-zero") == 0)) {
        settings.short_stroke_count = 0u;
        settings.long_stroke_count = 0u;
    } else if ((argc > 1) && (strcmp(argv[1], "short-length-zero") == 0)) {
        settings.short_length_tenths = 0u;
    } else if ((argc > 1) && (strcmp(argv[1], "long-length-zero") == 0)) {
        settings.long_length_tenths = 0u;
    }
    CoatingSettings_Validate(&settings);
    CoatingCycle_Init(&coating);
    MotionSequence_Init(&motion);

    can.position_tenths = 0u;
    can.speed_percent = 0u;
    can.moving = 0u;
    can.fault = 0u;
    can.previous_position_tenths = 255u;
    can.previous_speed_percent = 255u;

    /* Start at an unknown 7.3-inch physical location to exercise homing. */
    position = TenthsToCounts(73u, settings.feedback_counts_per_inch_x100);
    pulse_accumulator = 0.0;
    actual_rpm = 0.0;
    last_pulse_ms = 0ul;
    pulse_period_ms = 0ul;
    pulse_period_valid = 0u;
    measured_speed_x100 = 0;
    now_ms = 0ul;
    next_control_ms = 0ul;
    next_report_ms = 1000ul;
    previous_moving = 0u;
    previous_motion_state = motion.state;
    home_active = 1u;
    last_stroke_direction = 0u;
    transition_reversal_ok = 1u;
    saw_short = 0u;
    saw_long = 0u;
    next_command_ms = 0ul;

    csv = fopen("can_coating_pc.csv", "w");
    if (csv == NULL) {
        printf("Unable to create can_coating_pc.csv\n");
        return 1;
    }
    fputs("ms,operation,stroke,total,direction,target_tenths,speed_percent,"
          "moving,position_counts,target_counts,speed_cmd_x100,"
          "speed_fb_x100,duty,fault\n", csv);

    PrintSettings(&settings);
    CoatingCycle_Start(&coating, &settings);
    can.moving = 1u;
    printf("t=%6.2f operation=HOME moving=1 initial_position=%ld counts\n",
           0.0, position);

    while ((coating.operation != COAT_COMPLETE) &&
           (coating.operation != COAT_FAULT) &&
           (now_ms < SIM_TIMEOUT_MS)) {
        if (home_active != 0u) {
            demanded_rpm = -((double)settings.homing_speed_percent / 100.0) *
                           MOTOR_MAX_RPM;
        } else {
            demanded_rpm = ((double)motion.duty_command / 100.0) *
                           MOTOR_MAX_RPM;
        }

        actual_rpm += (demanded_rpm - actual_rpm) *
                      ((double)SIM_STEP_MS / MOTOR_TIME_CONSTANT_MS);
        pulse_accumulator += (actual_rpm / 60.0) * PULSES_PER_REV *
                             ((double)SIM_STEP_MS / 1000.0);
        while (pulse_accumulator >= 1.0) {
            ++position;
            pulse_accumulator -= 1.0;
            if (last_pulse_ms != 0ul) {
                pulse_period_ms = now_ms - last_pulse_ms;
                pulse_period_valid = 1u;
            }
            last_pulse_ms = now_ms;
        }
        while (pulse_accumulator <= -1.0) {
            --position;
            pulse_accumulator += 1.0;
            if (last_pulse_ms != 0ul) {
                pulse_period_ms = now_ms - last_pulse_ms;
                pulse_period_valid = 1u;
            }
            last_pulse_ms = now_ms;
        }

        if ((home_active != 0u) && (position <= 0l)) {
            position = 0l;
            pulse_accumulator = 0.0;
            actual_rpm = 0.0;
            home_active = 0u;
            can.moving = 0u;
            printf("t=%6.2f operation=HOME moving=0 position=0\n",
                   (double)now_ms / 1000.0);
            CoatingCycle_HomeComplete(&coating, &settings);
            next_command_ms = now_ms + CAN_COMMAND_GAP_MS;
        }

        if (now_ms >= next_control_ms) {
            if ((pulse_period_valid != 0u) &&
                ((now_ms - last_pulse_ms) <= PROX_STOP_TIMEOUT_MS) &&
                (pulse_period_ms != 0ul)) {
                measured_speed_x100 =
                    (signed int)(100000ul / pulse_period_ms);
                if (actual_rpm < 0.0) {
                    measured_speed_x100 = (signed int)-measured_speed_x100;
                }
            } else {
                measured_speed_x100 = 0;
            }

            if ((home_active == 0u) && (can.moving != 0u)) {
                MotionMove_Step(&motion, now_ms, position,
                                measured_speed_x100);
                if (motion.state == MOTION_COMPLETE) {
                    can.moving = 0u;
                    printf("t=%6.2f CAN moving=0 operation=%s stroke=%u/%u "
                           "position=%ld target=%ld\n",
                           (double)now_ms / 1000.0,
                           OperationName(coating.operation),
                           coating.stroke_number, coating.stroke_total,
                           position, motion.target_counts);
                    CoatingCycle_MoveComplete(&coating, &settings);
                    next_command_ms = now_ms + CAN_COMMAND_GAP_MS;
                } else if (motion.state == MOTION_FAULT) {
                    can.moving = 0u;
                    can.fault = motion.fault;
                    CoatingCycle_SetFault(&coating, motion.fault);
                }
            }

            if ((home_active == 0u) && (can.moving == 0u) &&
                (now_ms >= next_command_ms) &&
                CoatingCycle_TakeCommand(&coating, &command_position,
                                         &command_speed)) {
                if ((coating.operation == COAT_LONG_STROKE) &&
                    (saw_short != 0u) && (saw_long == 0u)) {
                    if (coating.direction_extend == last_stroke_direction) {
                        transition_reversal_ok = 0u;
                    }
                    saw_long = 1u;
                }
                if (coating.operation == COAT_SHORT_STROKE) {
                    saw_short = 1u;
                    last_stroke_direction = coating.direction_extend;
                } else if (coating.operation == COAT_LONG_STROKE) {
                    last_stroke_direction = coating.direction_extend;
                }

                if (!CanReceiveMove(&can, &motion, &settings, now_ms,
                                    position, command_position,
                                    command_speed)) {
                    printf("CAN duplicate command rejected\n");
                    CoatingCycle_SetFault(&coating, 3u);
                } else {
                    printf("t=%6.2f CAN RX operation=%s stroke=%u/%u dir=%s "
                           "position=%u.%u speed=%u%% target_counts=%ld "
                           "moving=%u\n",
                           (double)now_ms / 1000.0,
                           OperationName(coating.operation),
                           coating.stroke_number, coating.stroke_total,
                           coating.direction_extend ? "EXTEND" : "RETRACT",
                           command_position / 10u, command_position % 10u,
                           command_speed, motion.target_counts, can.moving);
                    if (can.moving == 0u) {
                        CoatingCycle_MoveComplete(&coating, &settings);
                        next_command_ms = now_ms + CAN_COMMAND_GAP_MS;
                    }
                }
            }
            next_control_ms += 10ul;
        }

        if ((now_ms >= next_report_ms) ||
            (previous_moving != can.moving) ||
            (previous_motion_state != motion.state)) {
            fprintf(csv, "%lu,%u,%u,%u,%s,%u,%u,%u,%ld,%ld,%d,%d,%d,%u\n",
                    now_ms, coating.operation, coating.stroke_number,
                    coating.stroke_total,
                    coating.direction_extend ? "extend" : "retract",
                    coating.target_tenths, coating.speed_percent, can.moving,
                    position, motion.target_counts,
                    motion.speed_command_x100, measured_speed_x100,
                    motion.duty_command, can.fault);
            previous_moving = can.moving;
            previous_motion_state = motion.state;
            if (now_ms >= next_report_ms) {
                next_report_ms += 1000ul;
            }
        }
        ++now_ms;
    }

    fclose(csv);
    printf("final: t=%.2f operation=%s position=%ld moving=%u fault=%u "
           "transition_reversal=%s\n",
           (double)now_ms / 1000.0, OperationName(coating.operation),
           position, can.moving, coating.fault,
           transition_reversal_ok ? "PASS" : "FAIL");
    printf("CSV telemetry written to can_coating_pc.csv\n");

    if ((coating.operation != COAT_COMPLETE) ||
        (coating.fault != 0u) || (transition_reversal_ok == 0u)) {
        return 1;
    }
    return 0;
}
