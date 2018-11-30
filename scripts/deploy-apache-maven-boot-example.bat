@ECHO OFF

CALL "%~dp0env.bat"

SET GOS_EXAMPLES_MAVEN_BOOT_WEB=%GOS_EXAMPLES_MAVEN%\solution\src\maven-solution-project-boot-web

ECHO Entering %GOS_EXAMPLES_MAVEN_BOOT_WEB%
PUSHD "%GOS_EXAMPLES_MAVEN_BOOT_WEB%"
CALL "%GOS_EXAMPLES_MVN_CMD%" tomcat7:deploy
POPD

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
