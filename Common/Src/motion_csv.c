#include "motion_csv.h"
#include "debug_visibility.h"

/* Append one character when space remains for it and the trailing NUL. */
FILE_LOCAL unsigned int AppendChar(char *buffer, unsigned int size,
                               unsigned int used, char value)
{
    if ((used + 1u) < size) {
        buffer[used] = value;
        ++used;
        buffer[used] = '\0';
    }
    return used;
}

/* Append an unsigned decimal value without using printf or division helpers. */
FILE_LOCAL unsigned int AppendUnsignedLong(char *buffer, unsigned int size,
                                       unsigned int used,
                                       unsigned long value)
{
    char digits[11];
    unsigned int count;

    count = 0u;
    do {
        digits[count] = (char)('0' + (value % 10ul));
        ++count;
        value /= 10ul;
    } while ((value != 0ul) && (count < sizeof(digits)));

    while (count != 0u) {
        --count;
        used = AppendChar(buffer, size, used, digits[count]);
    }
    return used;
}

/* Append a signed decimal value, including the most-negative long safely. */
FILE_LOCAL unsigned int AppendSignedLong(char *buffer, unsigned int size,
                                     unsigned int used, signed long value)
{
    unsigned long magnitude;

    if (value < 0l) {
        used = AppendChar(buffer, size, used, '-');
        magnitude = (unsigned long)(-(value + 1l)) + 1ul;
    } else {
        magnitude = (unsigned long)value;
    }
    return AppendUnsignedLong(buffer, size, used, magnitude);
}

/* Append the CSV field separator while preserving buffer termination. */
FILE_LOCAL unsigned int AppendComma(char *buffer, unsigned int size,
                                unsigned int used)
{
    return AppendChar(buffer, size, used, ',');
}

/*
 * MotionCsv_Header
 * Return the constant column heading shared by PC and embedded telemetry.
 * The returned string has static storage and must not be modified.
 */
const char *MotionCsv_Header(void)
{
    return "ms,state,cycle,position,target,speed_cmd_x100,"
           "speed_fb_x100,duty,fault,dropped\r\n";
}

/*
 * MotionCsv_Format
 * Format one complete controller sample as a CR/LF-terminated CSV record.
 * buffer_size includes the terminating NUL.  Fields that do not fit are
 * truncated safely, and the return value is the number of characters stored,
 * excluding the NUL.  This C89 formatter avoids the embedded printf library.
 */
unsigned int MotionCsv_Format(char *buffer,
                              unsigned int buffer_size,
                              unsigned long now_ms,
                              const MOTION_SEQUENCE *sequence,
                              signed long position_counts,
                              unsigned int dropped_records)
{
    unsigned int used;

    if (buffer_size == 0u) {
        return 0u;
    }
    buffer[0] = '\0';
    used = 0u;
    used = AppendUnsignedLong(buffer, buffer_size, used, now_ms);
    used = AppendComma(buffer, buffer_size, used);
    used = AppendUnsignedLong(buffer, buffer_size, used,
                              (unsigned long)sequence->state);
    used = AppendComma(buffer, buffer_size, used);
    used = AppendUnsignedLong(buffer, buffer_size, used,
                              (unsigned long)sequence->cycle);
    used = AppendComma(buffer, buffer_size, used);
    used = AppendSignedLong(buffer, buffer_size, used, position_counts);
    used = AppendComma(buffer, buffer_size, used);
    used = AppendSignedLong(buffer, buffer_size, used,
                            sequence->target_counts);
    used = AppendComma(buffer, buffer_size, used);
    used = AppendSignedLong(buffer, buffer_size, used,
                            (signed long)sequence->speed_command_x100);
    used = AppendComma(buffer, buffer_size, used);
    used = AppendSignedLong(buffer, buffer_size, used,
                            (signed long)sequence->measured_speed_x100);
    used = AppendComma(buffer, buffer_size, used);
    used = AppendSignedLong(buffer, buffer_size, used,
                            (signed long)sequence->duty_command);
    used = AppendComma(buffer, buffer_size, used);
    used = AppendUnsignedLong(buffer, buffer_size, used,
                              (unsigned long)sequence->fault);
    used = AppendComma(buffer, buffer_size, used);
    used = AppendUnsignedLong(buffer, buffer_size, used,
                              (unsigned long)dropped_records);
    used = AppendChar(buffer, buffer_size, used, '\r');
    used = AppendChar(buffer, buffer_size, used, '\n');
    return used;
}
