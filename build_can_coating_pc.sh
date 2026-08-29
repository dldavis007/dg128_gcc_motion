#!/bin/sh
set -eu
mkdir -p build
gcc -std=c89 -Wall -Wextra -pedantic -O0 -g -Icommon/include \
  common/src/motion_sequence.c common/src/coating_cycle.c \
  pc/src/can_coating_pc.c \
  -o build/can_coating_pc
exec build/can_coating_pc "$@"
