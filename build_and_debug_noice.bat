@echo off
setlocal
cd /d "%~dp0"

call build_embedded.bat
if errorlevel 1 (
  echo [ERROR] Build failed; NoICE was not started.
  exit /b 1
)

set "NOICE_EXE=C:\Program Files (x86)\NoICE\bin\NoICE12.exe"
if exist "%NOICE_EXE%" goto LAUNCH_NOICE

echo [ERROR] NoICE12.exe was not found at the configured path.
exit /b 1

:LAUNCH_NOICE
REM The generated session loads the STABS ELF, inlines the source mappings,
REM and installs the complete 58-variable diagnostic/menu watch list. Set NoICE
REM timed watch refresh to 500 ms or disable it before launching this session.
start "" "%NOICE_EXE%" "%CD%\build\dg128_smoke_debug.noi"
endlocal
