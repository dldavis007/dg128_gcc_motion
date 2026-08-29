#ifndef MOTION_SEQUENCE_H
#define MOTION_SEQUENCE_H

/* Public state values are intentionally numeric for NoICE watch display. */
#define MOTION_IDLE          0u
#define MOTION_EXTENDING     1u
#define MOTION_PAUSE_EXTEND  2u
#define MOTION_RETRACTING    3u
#define MOTION_PAUSE_RETRACT 4u
#define MOTION_COMPLETE      5u
#define MOTION_FAULT         6u

typedef struct
{
    unsigned char state;              /* MOTION_* state above. */
    unsigned char cycle;              /* Current cycle, starting at one. */
    unsigned char total_cycles;       /* Number of cycles requested. */
    unsigned char fault;              /* 0=none, 1=extend, 2=retract timeout. */
    signed long target_counts;        /* Requested absolute prox position. */
    signed char duty_command;         /* Signed PWM command, -100 to +100%. */
    signed int position_error_counts; /* Saturated diagnostic position error. */
    signed int speed_command_x100;    /* Requested prox counts/second x100. */
    signed int speed_limit_x100;      /* Absolute speed limit for this move. */
    signed int measured_speed_x100;   /* Feedback prox counts/second x100. */
    signed int speed_error_x100;      /* Command minus measured speed x100. */
    signed int speed_integral_x100;   /* PI integral contribution, % x100. */
    unsigned long state_start_ms;     /* Time current move/pause began. */
} MOTION_SEQUENCE;

/* Initialize an application-owned sequence object in the safe idle state. */
void MotionSequence_Init(MOTION_SEQUENCE *sequence);

/* Start the configured cycle sequence using now_ms as the time reference. */
void MotionSequence_Start(MOTION_SEQUENCE *sequence,
                          unsigned long now_ms,
                          signed long current_position);

/* Cancel motion and return the object to idle with zero commanded duty. */
void MotionSequence_Stop(MOTION_SEQUENCE *sequence);

/* Start one absolute point-to-point move with a caller-supplied speed limit. */
void MotionMove_Start(MOTION_SEQUENCE *sequence,
                      unsigned long now_ms,
                      signed long current_position,
                      signed long target_position,
                      signed int speed_limit_x100);

/* Run one update of a point-to-point move; normally called every 10 ms. */
void MotionMove_Step(MOTION_SEQUENCE *sequence,
                     unsigned long now_ms,
                     signed long current_position,
                     signed int measured_speed_x100);

/* Run one state/controller update; normally called every 10 milliseconds. */
void MotionSequence_Step(MOTION_SEQUENCE *sequence,
                         unsigned long now_ms,
                         signed long current_position,
                         signed int measured_speed_x100);

#endif
