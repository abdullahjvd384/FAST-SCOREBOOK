@echo off
REM FAST-SCOREBOOK Run Script
echo ========================================
echo   Running FAST-SCOREBOOK
echo ========================================
echo.

if not exist "bin\fast-scorebook.exe" (
    echo Executable not found! Building first...
    echo.
    call build.bat
    echo.
)

if exist "bin\fast-scorebook.exe" (
    bin\fast-scorebook.exe
) else (
    echo ERROR: Failed to build executable!
    pause
)
