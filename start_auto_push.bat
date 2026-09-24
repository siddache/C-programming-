@echo off
setlocal
cd /d "%~dp0"

if exist ".venv\Scripts\activate.bat" (
    call ".venv\Scripts\activate.bat"
    python auto_push.py
    exit /b %ERRORLEVEL%
)

where python >nul 2>nul
if not errorlevel 1 (
    python auto_push.py
    exit /b %ERRORLEVEL%
)

echo Python is not installed or not in PATH.
echo Install Python and try again.
echo If you are using Linux or macOS, run: ./start_auto_push.sh
pause
exit /b 1
