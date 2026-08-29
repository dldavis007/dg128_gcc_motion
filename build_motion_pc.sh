#!/bin/sh
set -eu
mkdir -p build
gcc -std=c89 -Wall -Wextra -pedantic -O0 -g -Icommon/include \
  common/src/motion_sequence.c common/src/motion_csv.c \
  pc/src/motion_sequence_pc.c \
  -o build/motion_sequence_pc
exec build/motion_sequence_pc
