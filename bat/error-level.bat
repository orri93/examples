@ECHO OFF
SETLOCAL ENABLEEXTENSIONS

REM How to check the exit code of the last command in batch file?
REM https://superuser.com/questions/194662/how-to-check-the-exit-code-of-the-last-command-in-batch-file

SET ROOT_DIR=.
CALL:MakeAbsolute ROOT_DIR "%~dp0"

FC "%ROOT_DIR%\absolute-path.bat" "%ROOT_DIR%\absolute-path.bat" > NUL
IF %ERRORLEVEL% EQU 0 GOTO fc_1_successful
ECHO The first FC command failed with error level %ERRORLEVEL%
EXIT /B 1
:fc_1_successful
ECHO The first FC command was successful

FC "%ROOT_DIR%\absolute-path.bat" "%ROOT_DIR%\error-level.bat" > NUL
IF %ERRORLEVEL% EQU 0 GOTO fc_2_successful
ECHO The second FC command failed with error level %ERRORLEVEL%
EXIT /B %ERRORLEVEL%
:fc_2_successful
ECHO The second FC command was successful

REM Done
GOTO:EOF

::----------------------------------------------------------------------------------
:: Function declarations
:: Handy to read http://www.dostips.com/DtTutoFunctions.php for how dos functions
:: work.
::----------------------------------------------------------------------------------
:MakeAbsolute file base -- makes a file name absolute considering a base path
::                      -- file [in,out] - variable with file name to be converted, or file name itself for result in stdout
::                      -- base [in,opt] - base path, leave blank for current directory
:$created 20060101 :$changed 20080219 :$categories Path
:$source http://www.dostips.com
SETLOCAL ENABLEDELAYEDEXPANSION
set "src=%~1"
if defined %1 set "src=!%~1!"
set "bas=%~2"
if not defined bas set "bas=%cd%"
for /f "tokens=*" %%a in ("%bas%.\%src%") do set "src=%%~fa"
( ENDLOCAL & REM RETURN VALUES
    IF defined %1 (SET %~1=%src%) ELSE ECHO.%src%
)
EXIT /b
