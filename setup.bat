@echo off
setlocal

echo Updating git submodules...

where /q git
if errorlevel 1 (
    echo git is not installed.
    exit /b 1
) ELSE (
    git submodule sync --recursive
    git submodule update --init --recursive
)

echo Creating a symbolic links to the folders...
mklink /D %~dp0\Falcor\Source\RenderPasses\Omstir %~dp0\RenderPasses
mklink /D %~dp0\Falcor\scripts\Omstir %~dp0\scripts
if errorlevel 1 goto error

echo Adding a new cmake subdirectory...
echo add_subdirectory(Omstir)>> %~dp0\Falcor\Source\RenderPasses\CMakeLists.txt

echo Running Falcor setup...
%~dp0\Falcor\setup.bat

echo Setup is done.

exit /b 0

:error
echo Failed to setup the project!
exit /b 1