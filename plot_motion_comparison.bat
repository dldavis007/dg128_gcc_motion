@echo off
setlocal
python tools\plot_motion_csv.py motion_embedded.csv motion_pc.csv motion_comparison.png
if errorlevel 1 (
  echo.
  echo If matplotlib is missing, run: python -m pip install matplotlib
  exit /b 1
)
start "" motion_comparison.png
endlocal
