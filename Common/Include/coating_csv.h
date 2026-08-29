#ifndef COATING_CSV_H
#define COATING_CSV_H

#include "coating_cycle.h"
#include "motion_sequence.h"

const char *CoatingCsv_Header(void);

unsigned int CoatingCsv_Format(char *buffer,
                               unsigned int buffer_size,
                               unsigned long now_ms,
                               const COATING_CYCLE *coating,
                               const MOTION_SEQUENCE *motion,
                               unsigned char moving,
                               signed long position_counts,
                               unsigned int dropped_records);

#endif
