@echo off
setlocal
if not exist build mkdir build
gcc -std=c89 -Wall -Wextra -pedantic -O0 -g -Icommon\include common\src\motion_sequence.c common\src\motion_csv.c pc\src\motion_sequence_pc.c -o build\motion_sequence_pc.exe
if errorlevel 1 exit /b 1
build\motion_sequence_pc.exe
endlocal
