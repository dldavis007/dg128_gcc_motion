#include "coating_csv.h"
#include "debug_visibility.h"

FILE_LOCAL unsigned int CoatAppendChar(char *buffer, unsigned int size,
                                       unsigned int used, char value)
{
    if ((used + 1u) < size) {
        buffer[used++] = value;
        buffer[used] = '\0';
    }
    return used;
}

FILE_LOCAL unsigned int CoatAppendUnsigned(char *buffer, unsigned int size,
                                           unsigned int used,
                                           unsigned long value)
{
    char digits[11];
    unsigned int count;

    count = 0u;
    do {
        digits[count++] = (char)('0' + (value % 10ul));
        value /= 10ul;
    } while ((value != 0ul) && (count < sizeof(digits)));
    while (count != 0u) {
        used = CoatAppendChar(buffer, size, used, digits[--count]);
    }
    return used;
}

FILE_LOCAL unsigned int CoatAppendSigned(char *buffer, unsigned int size,
                                         unsigned int used, signed long value)
{
    unsigned long magnitude;

    if (value < 0l) {
        used = CoatAppendChar(buffer, size, used, '-');
        magnitude = (unsigned long)(-(value + 1l)) + 1ul;
    } else {
        magnitude = (unsigned long)value;
    }
    return CoatAppendUnsigned(buffer, size, used, magnitude);
}

FILE_LOCAL unsigned int CoatAppendComma(char *buffer, unsigned int size,
                                        unsigned int used)
{
    return CoatAppendChar(buffer, size, used, ',');
}

const char *CoatingCsv_Header(void)
{
    return "ms,operation,stroke,total,direction,target_tenths,speed_percent,"
           "moving,position,target_counts,speed_cmd_x100,speed_fb_x100,"
           "duty,fault,dropped\r\n";
}

unsigned int CoatingCsv_Format(char *buffer,
                               unsigned int buffer_size,
                               unsigned long now_ms,
                               const COATING_CYCLE *coating,
                               const MOTION_SEQUENCE *motion,
                               unsigned char moving,
                               signed long position_counts,
                               unsigned int dropped_records)
{
    unsigned int used;

    if (buffer_size == 0u) {
        return 0u;
    }
    buffer[0] = '\0';
    used = 0u;
#define COAT_U(value) do { used = CoatAppendUnsigned(buffer, buffer_size, used, (unsigned long)(value)); used = CoatAppendComma(buffer, buffer_size, used); } while (0)
#define COAT_S(value) do { used = CoatAppendSigned(buffer, buffer_size, used, (signed long)(value)); used = CoatAppendComma(buffer, buffer_size, used); } while (0)
    COAT_U(now_ms);
    COAT_U(coating->operation);
    COAT_U(coating->stroke_number);
    COAT_U(coating->stroke_total);
    COAT_U(coating->direction_extend);
    COAT_U(coating->target_tenths);
    COAT_U(coating->speed_percent);
    COAT_U(moving);
    COAT_S(position_counts);
    COAT_S(motion->target_counts);
    COAT_S(motion->speed_command_x100);
    COAT_S(motion->measured_speed_x100);
    COAT_S(motion->duty_command);
    COAT_U(coating->fault);
    used = CoatAppendUnsigned(buffer, buffer_size, used,
                              (unsigned long)dropped_records);
#undef COAT_U
#undef COAT_S
    used = CoatAppendChar(buffer, buffer_size, used, '\r');
    used = CoatAppendChar(buffer, buffer_size, used, '\n');
    return used;
}
