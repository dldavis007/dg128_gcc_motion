@echo off
setlocal
cd /d "%~dp0"

set "NOICE_EXE=C:\Program Files (x86)\NoICE\bin\NoICE12.exe"
set "SESSION=build\dg128_smoke_debug.noi"
set "MODE_DESCRIPTION=reload the existing STABS ELF, symbols, source mappings, and watches"

if /I "%~1"=="noload" goto SELECT_NO_LOAD
goto CHECK_FILES

:SELECT_NO_LOAD
set "SESSION=build\dg128_smoke_reconnect.noi"
set "MODE_DESCRIPTION=restore source mappings and essential watches without loading target memory"

:CHECK_FILES
if not exist "%NOICE_EXE%" goto NO_NOICE
if not exist "%SESSION%" goto NO_SESSION

echo Closing any existing NoICE12 process...
taskkill /F /IM NoICE12.exe /T >nul 2>&1

echo Starting NoICE: %MODE_DESCRIPTION%.
if /I "%~1"=="noload" echo [NOTE] Use no-load only when the MCU contains this exact build.
start "" "%NOICE_EXE%" "%CD%\%SESSION%"
endlocal
exit /b 0

:NO_NOICE
echo [ERROR] NoICE12.exe was not found at:
echo         %NOICE_EXE%
endlocal
exit /b 1

:NO_SESSION
echo [ERROR] The generated NoICE session was not found:
echo         %CD%\%SESSION%
echo Run build_embedded.bat once to generate it.
endlocal
exit /b 1
