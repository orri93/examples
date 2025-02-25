@ECHO OFF

SETLOCAL ENABLEEXTENSIONS

SET GOS_ROOT_DIR=..
CALL:MakeAbsolute GOS_ROOT_DIR "%~dp0"

SET GOS_PROJECT_NAME=GOS Examples

SET GOS_EXE_CMAKE=cmake.exe
SET GOS_EXE_CTEST=ctest.exe

ECHO ---------------------------------------------------------------------------

ECHO Build script for the %GOS_PROJECT_NAME% project

REM Set build variables
SET GOS_BUILD_CONFIG=RelWithDebInfo

IF "%1" == "noclean" GOTO gos_not_clean
IF "%1" == "notclean" GOTO gos_not_clean
IF "%1" == "Noclean" GOTO gos_not_clean
IF "%1" == "Notclean" GOTO gos_not_clean
IF "%1" == "noClean" GOTO gos_not_clean
IF "%1" == "notClean" GOTO gos_not_clean
IF "%1" == "NoClean" GOTO gos_not_clean
IF "%1" == "NotClean" GOTO gos_not_clean
GOTO gos_check_not_clean_done
:gos_not_clean
ECHO Not Clean detected
SET GOS_NOT_CLEAN=NotClean
SHIFT
:gos_check_not_clean_done

IF "%1" == "nobuild" GOTO gos_not_build
IF "%1" == "nobuilds" GOTO gos_not_build
IF "%1" == "notbuild" GOTO gos_not_build
IF "%1" == "notbuilds" GOTO gos_not_build
IF "%1" == "noBuild" GOTO gos_not_build
IF "%1" == "noBuilds" GOTO gos_not_build
IF "%1" == "notBuild" GOTO gos_not_build
IF "%1" == "notBuilds" GOTO gos_not_build
IF "%1" == "NoBuild" GOTO gos_not_build
IF "%1" == "NoBuilds" GOTO gos_not_build
IF "%1" == "NotBuild" GOTO gos_not_build
IF "%1" == "NotBuilds" GOTO gos_not_build
SET GOS_BUILDING=ON
GOTO gos_no_build_done
:gos_not_build
ECHO No Build detected
SET GOS_BUILDING=OFF
SHIFT
:gos_no_build_done

IF "%1" == "" GOTO gos_no_build_number
SET GOS_BUILD_NUMBER=%1
GOTO gos_build_number_done
:gos_no_build_number
SET GOS_BUILD_NUMBER=0
:gos_build_number_done
SHIFT

REM Check and set environmental variables

SET GOS_PROJECT_BUILD_DIR=%GOS_ROOT_DIR%\build\%GOS_BUILD_CONFIG%
SET GOS_PROJECT_ARTIFACTS_DIR=%GOS_ROOT_DIR%\artifacts\%GOS_BUILD_CONFIG%
SET GOS_PROJECT_INCLUDE_DIR=%GOS_ROOT_DIR%\include

SET GOS_CMAKE_SYSTEM=Visual Studio 16 2019
SET GOS_CMAKE_PLATFORM=x64

REM --log-level=DEBUG ^
REM -DGOS_USE_GTEST_DISCOVER:BOOL=ON ^
REM -DCMAKE_BUILD_TYPE=%GOS_BUILD_CONFIG% ^

SET GOS_CMAKE_CREATE_OPTIONS=^
--graphviz="%GOS_PROJECT_ARTIFACTS_DIR%\share\graphviz\examples" ^
-DBUILD_TESTS:BOOL=ON ^
-DCMAKE_INSTALL_PREFIX:PATH="%GOS_PROJECT_ARTIFACTS_DIR%" ^
-G "%GOS_CMAKE_SYSTEM%" ^
-A %GOS_CMAKE_PLATFORM% "%GOS_ROOT_DIR%"

ECHO - GOS Build number is defined as %GOS_BUILD_NUMBER%
ECHO - Install path is defined as "%GOS_PROJECT_ARTIFACTS_DIR%"
ECHO - CMake buld system is defined as "%GOS_CMAKE_SYSTEM%"
ECHO - CMake buld platform is defined as "%GOS_CMAKE_PLATFORM%"
ECHO - CMake buld directory is defined as "%GOS_PROJECT_BUILD_DIR%"
ECHO - CMake buld configuration is defined as "%GOS_BUILD_CONFIG%"

SET GOS_CMAKE_BUILD_OPTIONS=--build "%GOS_PROJECT_BUILD_DIR%" --target ALL_BUILD --config %GOS_BUILD_CONFIG%
SET GOS_CMAKE_INSTALL_OPTIONS=--build "%GOS_PROJECT_BUILD_DIR%" --target install --config %GOS_BUILD_CONFIG%

SET GOS_CTEST_OPTIONS=--build-config %GOS_BUILD_CONFIG%

IF "%GOS_NOT_CLEAN%" == "NotClean" GOTO gos_do_not_clean
IF EXIST "%GOS_PROJECT_BUILD_DIR%" (
  ECHO The build folder already exists so deleting the old
  "%GOS_EXE_CMAKE%" -E remove_directory "%GOS_PROJECT_BUILD_DIR%"
)
IF EXIST "%GOS_PROJECT_ARTIFACTS_DIR%" (
  ECHO The artifacts folder already exists so deleting the old
  "%GOS_EXE_CMAKE%" -E remove_directory "%GOS_PROJECT_ARTIFACTS_DIR%"
)
:gos_do_not_clean

ECHO Creating a build folder %GOS_PROJECT_BUILD_DIR%
"%GOS_EXE_CMAKE%" -E make_directory "%GOS_PROJECT_BUILD_DIR%"

ECHO *** Creating a Build
SET GOS_CMAKE_CREATE_BUILD_CMD="%GOS_EXE_CMAKE%" -E chdir "%GOS_PROJECT_BUILD_DIR%" "%GOS_EXE_CMAKE%" %GOS_CMAKE_CREATE_OPTIONS%
ECHO %GOS_CMAKE_CREATE_BUILD_CMD%
%GOS_CMAKE_CREATE_BUILD_CMD%

IF "%GOS_BUILDING%" == "OFF" GOTO gos_do_not_build
ECHO *** Building
SET GOS_CMAKE_BUILD_CMD="%GOS_EXE_CMAKE%" %GOS_CMAKE_BUILD_OPTIONS%
ECHO %GOS_CMAKE_BUILD_CMD%
%GOS_CMAKE_BUILD_CMD%

ECHO *** Testing
SET GOS_CMAKE_CTEST_CMD="%GOS_EXE_CMAKE%" -E chdir "%GOS_PROJECT_BUILD_DIR%" "%GOS_EXE_CTEST%" %GOS_CTEST_OPTIONS%
ECHO %GOS_CMAKE_CTEST_CMD%
%GOS_CMAKE_CTEST_CMD%
:gos_do_not_build


ECHO *** Installing
SET GOS_CMAKE_INSTALL_CMD="%GOS_EXE_CMAKE%" %GOS_CMAKE_INSTALL_OPTIONS%
ECHO %GOS_CMAKE_INSTALL_CMD%
%GOS_CMAKE_INSTALL_CMD%

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

:inPath pathVar
::
::  Tests if the path stored within variable pathVar exists within PATH.
::
::  The result is returned as the ERRORLEVEL:
::    0 if the pathVar path is found in PATH.
::    1 if the pathVar path is not found in PATH.
::    2 if pathVar is missing or undefined or if PATH is undefined.
::
::  If the pathVar path is fully qualified, then it is logically compared
::  to each fully qualified path within PATH. The path strings don't have
::  to match exactly, they just need to be logically equivalent.
::
::  If the pathVar path is relative, then it is strictly compared to each
::  relative path within PATH. Case differences and double quotes are
::  ignored, but otherwise the path strings must match exactly.
::
::------------------------------------------------------------------------
::
:: Error checking
if "%~1"=="" exit /b 2
if not defined %~1 exit /b 2
if not defined path exit /b 2
::
:: Prepare to safely parse PATH into individual paths
setlocal DisableDelayedExpansion
set "var=%path:"=""%"
set "var=%var:^=^^%"
set "var=%var:&=^&%"
set "var=%var:|=^|%"
set "var=%var:<=^<%"
set "var=%var:>=^>%"
set "var=%var:;=^;^;%"
set var=%var:""="%
set "var=%var:"=""Q%"
set "var=%var:;;="S"S%"
set "var=%var:^;^;=;%"
set "var=%var:""="%"
setlocal EnableDelayedExpansion
set "var=!var:"Q=!"
set "var=!var:"S"S=";"!"
::
:: Remove quotes from pathVar and abort if it becomes empty
set "new=!%~1:"=!"
if not defined new exit /b 2
::
:: Determine if pathVar is fully qualified
echo("!new!"|findstr /i /r /c:^"^^\"[a-zA-Z]:[\\/][^\\/]" ^
                           /c:^"^^\"[\\][\\]" >nul ^
  && set "abs=1" || set "abs=0"
::
:: For each path in PATH, check if path is fully qualified and then do
:: proper comparison with pathVar.
:: Exit with ERRORLEVEL 0 if a match is found.
:: Delayed expansion must be disabled when expanding FOR variables
:: just in case the value contains !
for %%A in ("!new!\") do for %%B in ("!var!") do (
  if "!!"=="" endlocal
  for %%C in ("%%~B\") do (
    echo(%%B|findstr /i /r /c:^"^^\"[a-zA-Z]:[\\/][^\\/]" ^
                           /c:^"^^\"[\\][\\]" >nul ^
      && (if %abs%==1 if /i "%%~sA"=="%%~sC" exit /b 0) ^
      || (if %abs%==0 if /i "%%~A"=="%%~C" exit /b 0)
  )
)
:: No match was found so exit with ERRORLEVEL 1
exit /b 1
