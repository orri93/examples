@ECHO OFF

SET TUTORIAL_DIR=%~dp0

SET CMAKE_GENERATOR="Visual Studio 12 2013"

SET CMAKE_HOME=C:\Program Files\CMake

SET CMAKE_CLI=%CMAKE_HOME%\bin\cmake.exe

SET CMAKE_INSTALL_PREFIX=%TUTORIAL_DIR%\instdist

SET CMAKE_OPTIONS=-DCMAKE_INSTALL_PREFIX="%CMAKE_INSTALL_PREFIX%" -G %CMAKE_GENERATOR%

SET MSBUILD_CLI=msbuild
SET MSBUILD_OPTIONS=/m /t:Build /p:Configuration=Release ALL_BUILD.vcxproj

REM SET DEVELOPER_SETTINGS=%SOLUTION_DIR%\etc\developer\configuration.bat
REM ECHO Getting developer settings from %DEVELOPER_SETTINGS%
REM CALL "%DEVELOPER_SETTINGS%"

IF "%VS120COMNTOOLS%" == "" (
  ECHO Visual Studio 2013 Tool Path variable VS120COMNTOOLS is not defined
  goto GOTO:EOF
)

ECHO Visual Studio 2013 Tool Path is defined as %VS120COMNTOOLS%

SET BUILD_DIR=build
SET BUILD_PATH=%TUTORIAL_DIR%\%BUILD_DIR%

ECHO Enter Tutorial root directory %TUTORIAL_DIR% to check for previous build folder
PUSHD "%TUTORIAL_DIR%"
FOR %%i IN (%BUILD_PATH%) DO IF EXIST %%~si\NUL (
  ECHO   Delete previous build directory %BUILD_PATH%
  RMDIR  "%BUILD_PATH%" /S /Q
)

CALL "%VS120COMNTOOLS%vsvars32.bat"

ECHO   Recreating %BUILD_DIR% folder
MKDIR %BUILD_DIR%

ECHO Enter %BUILD_DIR%
PUSHD %BUILD_DIR%

"%CMAKE_CLI%" %CMAKE_OPTIONS% ..
%MSBUILD_CLI% %MSBUILD_OPTIONS%

POPD
POPD
