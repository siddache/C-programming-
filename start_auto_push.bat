@echo off
setlocal
cd /d "%~dp0"

if exist ".venv\Scripts\activate.bat" (
    call ".venv\Scripts\activate.bat"
    where python >nul 2>nul
    if not errorlevel 1 (
        python auto_push.py
        exit /b %ERRORLEVEL%
    )
    where py >nul 2>nul
    if not errorlevel 1 (
        py auto_push.py
        exit /b %ERRORLEVEL%
    )
)

where py >nul 2>nul
if not errorlevel 1 (
    py auto_push.py
    exit /b %ERRORLEVEL%
)

where python >nul 2>nul
if not errorlevel 1 (
    python auto_push.py
    exit /b %ERRORLEVEL%
)

echo Python was not found in the project venv or in PATH.
echo Install Python and ensure either "python" or "py" is available.
pause
exit /b 1
