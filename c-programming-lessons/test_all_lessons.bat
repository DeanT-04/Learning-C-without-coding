@echo off
REM Comprehensive C Programming Lessons Test Suite
REM Tests all lessons for compilation and basic functionality

setlocal enabledelayedexpansion

echo ========================================
echo C Programming Lessons Test Suite
echo ========================================
echo.

set TOTAL_TESTS=0
set PASSED_TESTS=0
set FAILED_TESTS=0
set FAILED_LESSONS=

REM Test all difficulty levels
call :test_difficulty_level "basics"
call :test_difficulty_level "intermediate" 
call :test_difficulty_level "pro"
call :test_difficulty_level "master"

echo.
echo ========================================
echo TEST SUMMARY
echo ========================================
echo Total Tests: %TOTAL_TESTS%
echo Passed: %PASSED_TESTS%
echo Failed: %FAILED_TESTS%

if %FAILED_TESTS% gtr 0 (
    echo.
    echo FAILED LESSONS:
    echo %FAILED_LESSONS%
    echo.
    echo Some tests failed. Please check the lessons above.
    exit /b 1
) else (
    echo.
    echo All tests passed successfully!
    exit /b 0
)

:test_difficulty_level
set level=%~1
echo.
echo Testing %level% level lessons...
echo ----------------------------------------

if not exist "%level%" (
    echo ERROR: %level% directory not found
    goto :eof
)

for /d %%d in ("%level%\lesson-*") do (
    call :test_lesson "%%d"
)
goto :eof

:test_lesson
set lesson_path=%~1
set /a TOTAL_TESTS+=1

echo Testing %lesson_path%...

REM Check if lesson directory exists
if not exist "%lesson_path%" (
    echo   ERROR: Lesson directory not found
    set /a FAILED_TESTS+=1
    set FAILED_LESSONS=%FAILED_LESSONS% %lesson_path%
    goto :eof
)

REM Check for required files
if not exist "%lesson_path%\main.c" (
    echo   ERROR: main.c not found
    set /a FAILED_TESTS+=1
    set FAILED_LESSONS=%FAILED_LESSONS% %lesson_path%
    goto :eof
)

if not exist "%lesson_path%\Makefile" (
    echo   ERROR: Makefile not found
    set /a FAILED_TESTS+=1
    set FAILED_LESSONS=%FAILED_LESSONS% %lesson_path%
    goto :eof
)

if not exist "%lesson_path%\README.md" (
    echo   ERROR: README.md not found
    set /a FAILED_TESTS+=1
    set FAILED_LESSONS=%FAILED_LESSONS% %lesson_path%
    goto :eof
)

REM Test compilation
pushd "%lesson_path%"
echo   Compiling...
make clean >nul 2>&1
make >nul 2>&1

if errorlevel 1 (
    echo   ERROR: Compilation failed
    popd
    set /a FAILED_TESTS+=1
    set FAILED_LESSONS=%FAILED_LESSONS% %lesson_path%
    goto :eof
)

echo   Compilation successful
set /a PASSED_TESTS+=1
popd
goto :eof