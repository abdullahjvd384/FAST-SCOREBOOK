@echo off
REM FAST-SCOREBOOK Build Script for Windows
echo ========================================
echo   FAST-SCOREBOOK Build Script
echo ========================================
echo.

REM Check if g++ is available
where g++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: g++ compiler not found!
    echo Please install MinGW or use Visual Studio Developer Command Prompt
    echo.
    echo Download MinGW from: https://sourceforge.net/projects/mingw/
    pause
    exit /b 1
)

echo [1/3] Checking directories...
if not exist "build" mkdir build
if not exist "bin" mkdir bin

echo [2/3] Compiling...
g++ -std=c++11 -Wall -Iinclude -o bin\fast-scorebook.exe src\main.cpp

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Compilation failed!
    pause
    exit /b 1
)

echo [3/3] Build successful!
echo.
echo ========================================
echo Executable created: bin\fast-scorebook.exe
echo ========================================
echo.
echo To run the program, execute:
echo   bin\fast-scorebook.exe
echo.
echo Or simply run: run.bat
echo.
pause
