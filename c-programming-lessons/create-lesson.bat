@echo off
REM Script to create a new lesson from templates
REM Usage: create-lesson.bat <difficulty> <lesson-number> <topic-name>
REM Example: create-lesson.bat basics 01 hello-world

if "%~3"=="" (
    echo Usage: create-lesson.bat ^<difficulty^> ^<lesson-number^> ^<topic-name^>
    echo Example: create-lesson.bat basics 01 hello-world
    echo.
    echo Available difficulties: basics, intermediate, pro, master
    exit /b 1
)

set DIFFICULTY=%1
set LESSON_NUM=%2
set TOPIC_NAME=%3
set LESSON_DIR=%DIFFICULTY%\lesson-%LESSON_NUM%-%TOPIC_NAME%

REM Validate difficulty level
if not "%DIFFICULTY%"=="basics" if not "%DIFFICULTY%"=="intermediate" if not "%DIFFICULTY%"=="pro" if not "%DIFFICULTY%"=="master" (
    echo Error: Invalid difficulty level. Use: basics, intermediate, pro, or master
    exit /b 1
)

REM Create lesson directory
if not exist "%LESSON_DIR%" mkdir "%LESSON_DIR%"

REM Copy template files
copy "templates\main.c" "%LESSON_DIR%\main.c" >nul
copy "templates\README.md" "%LESSON_DIR%\README.md" >nul
copy "templates\Makefile" "%LESSON_DIR%\Makefile" >nul

echo Created lesson directory: %LESSON_DIR%
echo.
echo Next steps:
echo 1. Edit %LESSON_DIR%\main.c and replace [PLACEHOLDERS]
echo 2. Update %LESSON_DIR%\README.md with lesson content
echo 3. Test compilation with: cd %LESSON_DIR% ^&^& make
echo.
echo Template files copied successfully!