@ECHO OFF

SET GOS_EXAMPLES_ROOT_DIR=..\..\..\..
CALL:MakeAbsolute GOS_EXAMPLES_ROOT_DIR "%~dp0"

ECHO GOS Example Root Directory is defined as %GOS_EXAMPLES_ROOT_DIR%

SET GOS_EXAMPLES_C_WEB_WASMC_EMSCRIPTEN_HELLO_ONE=%GOS_EXAMPLES_ROOT_DIR%\c\web\wasmc\emscripten\hello-one

ECHO GOS C Web Wasmc emscripten hello one Example Directory is defined as %GOS_EXAMPLES_C_WEB_WASMC_EMSCRIPTEN_HELLO_ONE%

ECHO Entering %GOS_EXAMPLES_C_WEB_WASMC_EMSCRIPTEN_HELLO_ONE%
PUSHD "%GOS_EXAMPLES_C_WEB_WASMC_EMSCRIPTEN_HELLO_ONE%"
python -m http.server
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
