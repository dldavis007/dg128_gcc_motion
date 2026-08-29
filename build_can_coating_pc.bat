@echo off
setlocal
if not exist build mkdir build
gcc -std=c89 -Wall -Wextra -pedantic -O0 -g -Icommon\include common\src\motion_sequence.c common\src\coating_cycle.c pc\src\can_coating_pc.c -o build\can_coating_pc.exe
if errorlevel 1 exit /b 1
build\can_coating_pc.exe %*
endlocal
