@echo off
setlocal
set "TOOLBIN=C:\Toolchains\GNU68HC12\bin"
if exist "%TOOLBIN%\m6811-elf-gcc.exe" (
  set "PREFIX=%TOOLBIN%\m6811-elf-"
) else (
  set "PREFIX=m6811-elf-"
)
set "DEBUG_VISIBILITY=-DNOICE_DEBUG_GLOBALS=1"
if /I "%~1"=="release" set "DEBUG_VISIBILITY="
set "COMMON_FLAGS=-m68hc12 -mshort -fshort-double -mlong-calls -std=c89 -Wall -W -O0 %DEBUG_VISIBILITY%"
set "FLAGS=%COMMON_FLAGS% -g"
set "STABS_FLAGS=%COMMON_FLAGS% -gstabs+"

"%PREFIX%gcc" --version >nul 2>&1
if errorlevel 1 (
  echo [ERROR] m6811-elf-gcc.exe was not found in %TOOLBIN% or on PATH.
  exit /b 1
)

if not exist build mkdir build
del /q build\dg128_*.o build\dg128_smoke.elf build\dg128_smoke.s19 build\dg128_smoke.map build\dg128_smoke_stabs.elf build\dg128_smoke_stabs.map build\dg128_smoke.noi build\dg128_smoke_debug.noi build\dg128_smoke_reconnect.noi build\dg128_smoke_debug_watches.noi 2>nul

"%PREFIX%gcc" %FLAGS% -Icommon\include -Iembedded\include -c embedded\src\dg128_startup.S -o build\dg128_startup.o || exit /b 1
"%PREFIX%gcc" %FLAGS% -Icommon\include -Iembedded\include -c embedded\src\dg128_vectors.S -o build\dg128_vectors.o || exit /b 1

REM Compile embedded C from its own directory for unambiguous debug paths.
pushd embedded\src
"%PREFIX%gcc" %FLAGS% -I..\include -I..\..\common\include -c dg128_smoke.c -o ..\..\build\dg128_smoke.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %STABS_FLAGS% -I..\include -I..\..\common\include -c dg128_smoke.c -o ..\..\build\dg128_smoke_stabs.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %FLAGS% -I..\include -I..\..\common\include -c noice_vuart.c -o ..\..\build\noice_vuart.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %STABS_FLAGS% -I..\include -I..\..\common\include -c noice_vuart.c -o ..\..\build\noice_vuart_stabs.o
if errorlevel 1 (
  popd
  exit /b 1
)
popd

REM Compile portable shared C from its own directory for clear NoICE sources.
pushd common\src
"%PREFIX%gcc" %FLAGS% -I..\include -c motion_sequence.c -o ..\..\build\motion_sequence.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %STABS_FLAGS% -I..\include -c motion_sequence.c -o ..\..\build\motion_sequence_stabs.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %FLAGS% -I..\include -c coating_cycle.c -o ..\..\build\coating_cycle.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %STABS_FLAGS% -I..\include -c coating_cycle.c -o ..\..\build\coating_cycle_stabs.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %FLAGS% -I..\include -c motion_csv.c -o ..\..\build\motion_csv.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %STABS_FLAGS% -I..\include -c motion_csv.c -o ..\..\build\motion_csv_stabs.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %FLAGS% -I..\include -c coating_csv.c -o ..\..\build\coating_csv.o
if errorlevel 1 (
  popd
  exit /b 1
)
"%PREFIX%gcc" %STABS_FLAGS% -I..\include -c coating_csv.c -o ..\..\build\coating_csv_stabs.o
if errorlevel 1 (
  popd
  exit /b 1
)
popd

"%PREFIX%gcc" %FLAGS% -Wl,-T,embedded\linker\dg128_fixed.x -Wl,-Map,build\dg128_smoke.map build\dg128_startup.o build\dg128_vectors.o build\dg128_smoke.o build\motion_sequence.o build\coating_cycle.o build\motion_csv.o build\coating_csv.o build\noice_vuart.o -o build\dg128_smoke.elf || exit /b 1

REM Alternate debug file for NoICE versions that reject this GCC's DWARF lines.
"%PREFIX%gcc" %STABS_FLAGS% -Wl,-T,embedded\linker\dg128_fixed.x -Wl,-Map,build\dg128_smoke_stabs.map build\dg128_startup.o build\dg128_vectors.o build\dg128_smoke_stabs.o build\motion_sequence_stabs.o build\coating_cycle_stabs.o build\motion_csv_stabs.o build\coating_csv_stabs.o build\noice_vuart_stabs.o -o build\dg128_smoke_stabs.elf || exit /b 1

REM NoICE 9.8 loads the ELF symbols but does not reliably import this old
REM GCC's source mappings.  Generate explicit FILE/FUNCTION/LINE commands.
python tools\stabs_to_noice.py "%PREFIX%objdump" build\dg128_smoke_stabs.elf embedded\src\dg128_smoke.c build\dg128_smoke.noi build\dg128_smoke_debug.noi || exit /b 1

"%PREFIX%objcopy" -O srec build\dg128_smoke.elf build\dg128_smoke.s19 || exit /b 1
"%PREFIX%size" -A build\dg128_smoke.elf
"%PREFIX%objdump" -h -f build\dg128_smoke.elf

echo.
echo Build complete.
if /I "%~1"=="release" echo Symbol visibility: RELEASE ^(normal static linkage^)
if /I not "%~1"=="release" echo Symbol visibility: NOICE DEBUG ^(file-local symbols made global^)
echo NoICE DWARF input: build\dg128_smoke.elf
echo NoICE STABS input: build\dg128_smoke_stabs.elf
echo NoICE source mappings: build\dg128_smoke.noi
echo NoICE automated session: build\dg128_smoke_debug.noi
echo NoICE no-load reconnect: build\dg128_smoke_reconnect.noi
echo NoICE standalone full watches: build\dg128_smoke_debug_watches.noi
echo NoICE BDM Virtual UART: RAM 0x2000/0x2001, CSV every 250 ms
echo Programmer input after validation: build\dg128_smoke.s19
endlocal
