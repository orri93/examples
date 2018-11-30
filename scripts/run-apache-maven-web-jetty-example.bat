@ECHO OFF

SET GOS_EXAMPLES_ROOT_DIR=..
CALL:MakeAbsolute GOS_EXAMPLES_ROOT_DIR "%~dp0"

SET M2_HOME=C:\opt\apache\apache-maven-3.5.3
SET GOS_EXAMPLES_MVN_CMD=%M2_HOME%\bin\mvn.cmd

SET GOS_EXAMPLES_APACHE=%GOS_EXAMPLES_ROOT_DIR%\apache
SET GOS_EXAMPLES_MAVEN=%GOS_EXAMPLES_APACHE%\maven

SET GOS_EXAMPLES_MAVEN_WEB=%GOS_EXAMPLES_MAVEN%\solution\src\maven-solution-project-web


ECHO Entering %GOS_EXAMPLES_MAVEN_WEB%
PUSHD "%GOS_EXAMPLES_MAVEN_WEB%"
"%GOS_EXAMPLES_MVN_CMD%" compile jetty:run
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
