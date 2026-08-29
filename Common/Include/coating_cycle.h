#ifndef COATING_CYCLE_H
#define COATING_CYCLE_H

/* Coating scheduler operation values are numeric for simple CAN/NoICE display. */
#define COAT_IDLE             0u
#define COAT_HOME             1u
#define COAT_POSITION_START   2u
#define COAT_SHORT_STROKE     3u
#define COAT_LONG_STROKE      4u
#define COAT_COMPLETE         5u
#define COAT_FAULT            6u

/* Menu-style settings. Distances use 0.1 inch and speeds use percent. */
typedef struct
{
    unsigned char actuator_length_tenths;
    unsigned char short_stroke_count;
    unsigned char short_length_tenths;
    unsigned char long_stroke_count;
    unsigned char long_length_tenths;
    unsigned char positioning_speed_percent;
    unsigned char homing_speed_percent;
    unsigned char fast_stroke_count;
    unsigned char short_fast_speed_percent;
    unsigned char short_slow_speed_percent;
    unsigned char long_fast_speed_percent;
    unsigned char long_slow_speed_percent;
    unsigned int feedback_counts_per_inch_x100;
    unsigned int motor_max_speed_counts_x100;
} COATING_SETTINGS;

typedef struct
{
    unsigned char operation;
    unsigned char stroke_number;
    unsigned char stroke_total;
    unsigned char target_tenths;
    unsigned char speed_percent;
    unsigned char direction_extend;
    unsigned char command_pending;
    unsigned char fault;
} COATING_CYCLE;

/* Install a representative menu configuration used by the PC simulation. */
void CoatingSettings_Default(COATING_SETTINGS *settings);

/* Validate and clamp menu settings to a safe, internally consistent range. */
void CoatingSettings_Validate(COATING_SETTINGS *settings);

/* Initialize or start one coating cycle; Start begins with the home operation. */
void CoatingCycle_Init(COATING_CYCLE *cycle);
void CoatingCycle_Start(COATING_CYCLE *cycle,
                        const COATING_SETTINGS *settings);

/* Notify the scheduler that homing or the current CAN move has completed. */
void CoatingCycle_HomeComplete(COATING_CYCLE *cycle,
                               const COATING_SETTINGS *settings);
void CoatingCycle_MoveComplete(COATING_CYCLE *cycle,
                               const COATING_SETTINGS *settings);
void CoatingCycle_SetFault(COATING_CYCLE *cycle, unsigned char fault);

/* Fetch and clear the next two-byte CAN command: position, then speed. */
unsigned char CoatingCycle_TakeCommand(COATING_CYCLE *cycle,
                                       unsigned char *position_tenths,
                                       unsigned char *speed_percent);

#endif
