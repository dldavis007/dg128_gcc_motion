#include <stdio.h>
#include "motion_sequence.h"
#include "motion_csv.h"

#define PULSES_PER_REV 9.0
#define MOTOR_MAX_RPM 40.0
#define SIM_STEP_MS 1ul
#define MOTOR_TIME_CONSTANT_MS 180.0
#define PROX_STOP_TIMEOUT_MS 3000ul

/*
 * main
 * Run the portable controller against a deterministic first-order motor model.
 * The model converts signed duty to shaft speed and nine prox pulses/revolution,
 * calls the same 10 ms MotionSequence_Step used by the DG128, writes 250 ms CSV
 * samples, and returns nonzero if the simulated sequence faults or times out.
 */
int main(void)
{
    MOTION_SEQUENCE sequence;
    unsigned long now_ms;
    unsigned long next_control_ms;
    unsigned long next_report_ms;
    unsigned long next_csv_ms;
    unsigned char previous_state;
    signed long position;
    double pulse_accumulator;
    double demanded_rpm;
    double actual_rpm;
    unsigned long last_pulse_ms;
    unsigned long pulse_period_ms;
    unsigned char pulse_period_valid;
    signed int measured_speed_x100;
    FILE *csv_file;
    char csv_line[96];

    MotionSequence_Init(&sequence);
    position = 0l;
    pulse_accumulator = 0.0;
    actual_rpm = 0.0;
    last_pulse_ms = 0ul;
    pulse_period_ms = 0ul;
    pulse_period_valid = 0u;
    measured_speed_x100 = 0;
    now_ms = 0ul;
    next_control_ms = 0ul;
    next_report_ms = 5000ul;
    next_csv_ms = 0ul;
    csv_file = fopen("motion_pc.csv", "w");
    if (csv_file == NULL) {
        printf("Unable to create motion_pc.csv\n");
        return 1;
    }
    MotionSequence_Start(&sequence, now_ms, position);
    previous_state = sequence.state;
    fputs(MotionCsv_Header(), csv_file);

    printf("PC cascaded position/speed control: 49 counts, 2 cycles, 95%% maximum\n");

    while ((sequence.state != MOTION_COMPLETE) &&
           (sequence.state != MOTION_FAULT) &&
           (now_ms < 180000ul)) {
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
            MotionSequence_Step(&sequence, now_ms, position,
                                measured_speed_x100);
            next_control_ms += 10ul;
            if (sequence.state != previous_state) {
                printf("t=%6.2f state=%u cycle=%u position=%ld duty=%d speed=%.2f\n",
                       (double)now_ms / 1000.0,
                       (unsigned int)sequence.state,
                       (unsigned int)sequence.cycle,
                       position,
                       (int)sequence.duty_command,
                       (double)measured_speed_x100 / 100.0);
                previous_state = sequence.state;
            }
        }

        if (now_ms >= next_report_ms) {
            printf("t=%6.2f state=%u position=%ld target=%ld "
                   "speed_cmd=%.2f speed_fb=%.2f duty=%d\n",
                   (double)now_ms / 1000.0,
                   (unsigned int)sequence.state,
                   position,
                   sequence.target_counts,
                   (double)sequence.speed_command_x100 / 100.0,
                   (double)measured_speed_x100 / 100.0,
                   (int)sequence.duty_command);
            next_report_ms += 5000ul;
        }

        if (now_ms >= next_csv_ms) {
            MotionCsv_Format(csv_line, sizeof(csv_line), now_ms,
                             &sequence, position, 0u);
            fputs(csv_line, csv_file);
            next_csv_ms += MOTION_TELEMETRY_PERIOD_MS;
        }

        demanded_rpm = ((double)sequence.duty_command / 100.0) * MOTOR_MAX_RPM;
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
        now_ms += SIM_STEP_MS;
    }

    printf("final: t=%.2f state=%u cycles=%u position=%ld fault=%u\n",
           (double)now_ms / 1000.0,
           (unsigned int)sequence.state,
           (unsigned int)sequence.cycle,
           position,
           (unsigned int)sequence.fault);
    MotionCsv_Format(csv_line, sizeof(csv_line), now_ms,
                     &sequence, position, 0u);
    fputs(csv_line, csv_file);
    fclose(csv_file);
    printf("CSV telemetry written to motion_pc.csv at %lu ms intervals.\n",
           MOTION_TELEMETRY_PERIOD_MS);
    return (sequence.state == MOTION_COMPLETE) ? 0 : 1;
}
