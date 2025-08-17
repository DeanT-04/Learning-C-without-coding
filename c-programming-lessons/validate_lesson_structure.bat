@echo off
REM Lesson Structure Validator
REM Validates that all lessons follow the expected structure and naming conventions

setlocal enabledelayedexpansion

echo Validating lesson structure and organization...
echo.

set TOTAL_CHECKS=0
set PASSED_CHECKS=0
set FAILED_CHECKS=0

REM Define expected lesson structure for each difficulty level
set "BASICS_LESSONS=lesson-01-hello-world lesson-02-variables-types lesson-03-operators lesson-04-control-structures lesson-05-loops lesson-06-functions"
set "INTERMEDIATE_LESSONS=lesson-01-pointers lesson-02-arrays-strings lesson-03-advanced-functions lesson-04-scope-storage lesson-05-preprocessor lesson-06-file-io"
set "PRO_LESSONS=lesson-01-structures-unions lesson-02-dynamic-memory lesson-03-advanced-file-handling lesson-04-data-structures lesson-05-function-pointers lesson-06-multi-file-projects"
set "MASTER_LESSONS=lesson-01-advanced-algorithms lesson-02-system-programming lesson-03-memory-optimization lesson-04-bit-manipulation lesson-05-advanced-debugging lesson-06-performance-analysis"

REM Validate directory structure
call :validate_difficulty_structure "basics" "%BASICS_LESSONS%"
call :validate_difficulty_structure "intermediate" "%INTERMEDIATE_LESSONS%"
call :validate_difficulty_structure "pro" "%PRO_LESSONS%"
call :validate_difficulty_structure "master" "%MASTER_LESSONS%"

REM Validate templates directory
call :validate_templates

echo.
echo ========================================
echo STRUCTURE VALIDATION SUMMARY
echo ========================================
echo Total Checks: %TOTAL_CHECKS%
echo Passed: %PASSED_CHECKS%
echo Failed: %FAILED_CHECKS%

if %FAILED_CHECKS% gtr 0 (
    echo.
    echo ❌ Structure validation failed!
    exit /b 1
) else (
    echo.
    echo ✅ All structure validation checks passed!
    exit /b 0
)

:validate_difficulty_structure
set level=%~1
set expected_lessons=%~2

echo Validating %level% level structure...

REM Check if difficulty level directory exists
set /a TOTAL_CHECKS+=1
if not exist "%level%" (
    echo   ERROR: %level% directory not found
    set /a FAILED_CHECKS+=1
    goto :eof
)
set /a PASSED_CHECKS+=1

REM Check each expected lesson
for %%l in (%expected_lessons%) do (
    set /a TOTAL_CHECKS+=1
    if not exist "%level%\%%l" (
        echo   ERROR: Missing lesson %level%\%%l
        set /a FAILED_CHECKS+=1
    ) else (
        echo   ✓ Found %level%\%%l
        set /a PASSED_CHECKS+=1
        
        REM Validate lesson contents
        call :validate_lesson_contents "%level%\%%l"
    )
)
goto :eof

:validate_lesson_contents
set lesson_path=%~1

REM Check for required files in lesson
set required_files=main.c Makefile README.md
for %%f in (%required_files%) do (
    set /a TOTAL_CHECKS+=1
    if not exist "%lesson_path%\%%f" (
        echo     ERROR: Missing %lesson_path%\%%f
        set /a FAILED_CHECKS+=1
    ) else (
        set /a PASSED_CHECKS+=1
    )
)
goto :eof

:validate_templates
echo Validating templates directory...

set /a TOTAL_CHECKS+=1
if not exist "templates" (
    echo   ERROR: templates directory not found
    set /a FAILED_CHECKS+=1
    goto :eof
)
set /a PASSED_CHECKS+=1

REM Check template files
set template_files=main.c Makefile README.md
for %%f in (%template_files%) do (
    set /a TOTAL_CHECKS+=1
    if not exist "templates\%%f" (
        echo   ERROR: Missing templates\%%f
        set /a FAILED_CHECKS+=1
    ) else (
        echo   ✓ Found templates\%%f
        set /a PASSED_CHECKS+=1
    )
)
goto :eof