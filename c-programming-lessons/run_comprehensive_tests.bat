@echo off
REM Comprehensive Test Runner for C Programming Lessons
REM Runs all tests including compilation, code quality, and validation

echo ========================================
echo C Programming Lessons Comprehensive Test Suite
echo ========================================
echo.

set OVERALL_SUCCESS=1

REM Run compilation tests
echo [1/3] Running compilation tests...
echo ----------------------------------------
call test_all_lessons.bat
if errorlevel 1 (
    echo Compilation tests failed!
    set OVERALL_SUCCESS=0
) else (
    echo Compilation tests passed!
)

echo.

REM Run code quality validation
echo [2/3] Running code quality validation...
echo ----------------------------------------
python validate_code_quality.py
if errorlevel 1 (
    echo Code quality validation failed!
    set OVERALL_SUCCESS=0
) else (
    echo Code quality validation passed!
)

echo.

REM Run lesson structure validation
echo [3/3] Running lesson structure validation...
echo ----------------------------------------
call validate_lesson_structure.bat
if errorlevel 1 (
    echo Lesson structure validation failed!
    set OVERALL_SUCCESS=0
) else (
    echo Lesson structure validation passed!
)

echo.
echo ========================================
echo COMPREHENSIVE TEST RESULTS
echo ========================================

if %OVERALL_SUCCESS%==1 (
    echo ✅ All tests passed successfully!
    echo The C Programming Lessons project is ready for use.
    exit /b 0
) else (
    echo ❌ Some tests failed!
    echo Please review the output above and fix the issues.
    exit /b 1
)