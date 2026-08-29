#ifndef MOTION_CSV_H
#define MOTION_CSV_H

#include "motion_sequence.h"

#define MOTION_TELEMETRY_PERIOD_MS 250ul /* Shared PC/embedded sample period. */

/* Return the constant CR/LF-terminated CSV column heading. */
const char *MotionCsv_Header(void);

/* Format one bounded, NUL-terminated controller telemetry record. */
unsigned int MotionCsv_Format(char *buffer,
                              unsigned int buffer_size,
                              unsigned long now_ms,
                              const MOTION_SEQUENCE *sequence,
                              signed long position_counts,
                              unsigned int dropped_records);

#endif
