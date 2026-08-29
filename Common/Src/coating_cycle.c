#include "coating_cycle.h"
#include "debug_visibility.h"

#define MIN_SPEED_PERCENT 10u
#define MAX_SPEED_PERCENT 95u

FILE_LOCAL unsigned char ClampSpeed(unsigned char speed)
{
    if (speed < MIN_SPEED_PERCENT) {
        return MIN_SPEED_PERCENT;
    }
    if (speed > MAX_SPEED_PERCENT) {
        return MAX_SPEED_PERCENT;
    }
    return speed;
}

FILE_LOCAL unsigned char StrokeLow(unsigned char actuator_length,
                               unsigned char stroke_length)
{
    return (unsigned char)((actuator_length - stroke_length) / 2u);
}

FILE_LOCAL unsigned char StrokeHigh(unsigned char actuator_length,
                                unsigned char stroke_length)
{
    unsigned char low;

    low = StrokeLow(actuator_length, stroke_length);
    return (unsigned char)(low + stroke_length);
}

FILE_LOCAL unsigned char StrokeSpeed(const COATING_SETTINGS *settings,
                                 unsigned char operation,
                                 unsigned char stroke_number)
{
    unsigned char fast;

    fast = (stroke_number <= settings->fast_stroke_count) ? 1u : 0u;
    if (operation == COAT_SHORT_STROKE) {
        return fast ? settings->short_fast_speed_percent :
                      settings->short_slow_speed_percent;
    }
    return fast ? settings->long_fast_speed_percent :
                  settings->long_slow_speed_percent;
}

FILE_LOCAL unsigned char ShortEnabled(const COATING_SETTINGS *settings)
{
    return ((settings->short_stroke_count != 0u) &&
            (settings->short_length_tenths != 0u)) ? 1u : 0u;
}

FILE_LOCAL unsigned char LongEnabled(const COATING_SETTINGS *settings)
{
    return ((settings->long_stroke_count != 0u) &&
            (settings->long_length_tenths != 0u)) ? 1u : 0u;
}

FILE_LOCAL void QueuePositioning(COATING_CYCLE *cycle,
                             const COATING_SETTINGS *settings,
                             unsigned char next_operation)
{
    unsigned char length;

    length = (next_operation == COAT_SHORT_STROKE) ?
             settings->short_length_tenths : settings->long_length_tenths;
    cycle->operation = COAT_POSITION_START;
    cycle->stroke_number = 0u;
    cycle->stroke_total = (next_operation == COAT_SHORT_STROKE) ?
                          settings->short_stroke_count :
                          settings->long_stroke_count;
    cycle->target_tenths = StrokeLow(settings->actuator_length_tenths, length);
    cycle->speed_percent = settings->positioning_speed_percent;
    cycle->direction_extend = 1u;
    cycle->command_pending = 1u;
}

FILE_LOCAL void QueueStroke(COATING_CYCLE *cycle,
                        const COATING_SETTINGS *settings,
                        unsigned char operation,
                        unsigned char stroke_number,
                        unsigned char direction_extend)
{
    unsigned char length;

    length = (operation == COAT_SHORT_STROKE) ?
             settings->short_length_tenths : settings->long_length_tenths;
    cycle->operation = operation;
    cycle->stroke_number = stroke_number;
    cycle->stroke_total = (operation == COAT_SHORT_STROKE) ?
                          settings->short_stroke_count :
                          settings->long_stroke_count;
    cycle->direction_extend = direction_extend;
    cycle->target_tenths = direction_extend ?
        StrokeHigh(settings->actuator_length_tenths, length) :
        StrokeLow(settings->actuator_length_tenths, length);
    cycle->speed_percent = StrokeSpeed(settings, operation, stroke_number);
    cycle->command_pending = 1u;
}

void CoatingSettings_Default(COATING_SETTINGS *settings)
{
    settings->actuator_length_tenths = 100u; /* 10.0 inches. */
    settings->short_stroke_count = 4u;
    settings->short_length_tenths = 40u;     /* Centered 4.0-inch passes. */
    settings->long_stroke_count = 4u;
    settings->long_length_tenths = 100u;     /* Full 10.0-inch passes. */
    settings->positioning_speed_percent = 75u;
    settings->homing_speed_percent = 35u;
    settings->fast_stroke_count = 2u;
    settings->short_fast_speed_percent = 70u;
    settings->short_slow_speed_percent = 40u;
    settings->long_fast_speed_percent = 90u;
    settings->long_slow_speed_percent = 60u;
    settings->feedback_counts_per_inch_x100 = 485u;
    settings->motor_max_speed_counts_x100 = 625u;
}

void CoatingSettings_Validate(COATING_SETTINGS *settings)
{
    if (settings->actuator_length_tenths == 0u) {
        settings->actuator_length_tenths = 1u;
    }
    if (settings->short_length_tenths > settings->actuator_length_tenths) {
        settings->short_length_tenths = settings->actuator_length_tenths;
    }
    if (settings->long_length_tenths > settings->actuator_length_tenths) {
        settings->long_length_tenths = settings->actuator_length_tenths;
    }
    settings->positioning_speed_percent =
        ClampSpeed(settings->positioning_speed_percent);
    settings->homing_speed_percent = ClampSpeed(settings->homing_speed_percent);
    settings->short_fast_speed_percent =
        ClampSpeed(settings->short_fast_speed_percent);
    settings->short_slow_speed_percent =
        ClampSpeed(settings->short_slow_speed_percent);
    settings->long_fast_speed_percent =
        ClampSpeed(settings->long_fast_speed_percent);
    settings->long_slow_speed_percent =
        ClampSpeed(settings->long_slow_speed_percent);
    if (settings->feedback_counts_per_inch_x100 == 0u) {
        settings->feedback_counts_per_inch_x100 = 1u;
    }
    if (settings->motor_max_speed_counts_x100 == 0u) {
        settings->motor_max_speed_counts_x100 = 1u;
    }
}

void CoatingCycle_Init(COATING_CYCLE *cycle)
{
    cycle->operation = COAT_IDLE;
    cycle->stroke_number = 0u;
    cycle->stroke_total = 0u;
    cycle->target_tenths = 0u;
    cycle->speed_percent = 0u;
    cycle->direction_extend = 0u;
    cycle->command_pending = 0u;
    cycle->fault = 0u;
}

void CoatingCycle_Start(COATING_CYCLE *cycle,
                        const COATING_SETTINGS *settings)
{
    (void)settings;
    CoatingCycle_Init(cycle);
    cycle->operation = COAT_HOME;
}

void CoatingCycle_HomeComplete(COATING_CYCLE *cycle,
                               const COATING_SETTINGS *settings)
{
    if (ShortEnabled(settings) != 0u) {
        QueuePositioning(cycle, settings, COAT_SHORT_STROKE);
    } else if (LongEnabled(settings) != 0u) {
        QueuePositioning(cycle, settings, COAT_LONG_STROKE);
    } else {
        cycle->operation = COAT_COMPLETE;
    }
}

void CoatingCycle_MoveComplete(COATING_CYCLE *cycle,
                               const COATING_SETTINGS *settings)
{
    unsigned char next_direction;

    if (cycle->operation == COAT_POSITION_START) {
        if (ShortEnabled(settings) != 0u) {
            QueueStroke(cycle, settings, COAT_SHORT_STROKE, 1u, 1u);
        } else {
            QueueStroke(cycle, settings, COAT_LONG_STROKE, 1u, 1u);
        }
        return;
    }

    if (cycle->operation == COAT_SHORT_STROKE) {
        next_direction = cycle->direction_extend ? 0u : 1u;
        if (cycle->stroke_number < settings->short_stroke_count) {
            QueueStroke(cycle, settings, COAT_SHORT_STROKE,
                        (unsigned char)(cycle->stroke_number + 1u),
                        next_direction);
        } else if (LongEnabled(settings) != 0u) {
            /* Preserve reversal across the short-to-long transition. */
            QueueStroke(cycle, settings, COAT_LONG_STROKE, 1u,
                        next_direction);
        } else {
            cycle->operation = COAT_COMPLETE;
            cycle->command_pending = 0u;
        }
        return;
    }

    if (cycle->operation == COAT_LONG_STROKE) {
        next_direction = cycle->direction_extend ? 0u : 1u;
        if (cycle->stroke_number < settings->long_stroke_count) {
            QueueStroke(cycle, settings, COAT_LONG_STROKE,
                        (unsigned char)(cycle->stroke_number + 1u),
                        next_direction);
        } else {
            cycle->operation = COAT_COMPLETE;
            cycle->command_pending = 0u;
        }
    }
}

void CoatingCycle_SetFault(COATING_CYCLE *cycle, unsigned char fault)
{
    cycle->operation = COAT_FAULT;
    cycle->fault = fault;
    cycle->command_pending = 0u;
}

unsigned char CoatingCycle_TakeCommand(COATING_CYCLE *cycle,
                                       unsigned char *position_tenths,
                                       unsigned char *speed_percent)
{
    if (cycle->command_pending == 0u) {
        return 0u;
    }
    *position_tenths = cycle->target_tenths;
    *speed_percent = cycle->speed_percent;
    cycle->command_pending = 0u;
    return 1u;
}
