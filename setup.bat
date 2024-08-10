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

echo Running deps setup...
call %~dp0\deps\setup.bat
if errorlevel 1 goto error

echo Setup is done.
exit /b 0

:error
echo Failed to setup the project!
exit /b 1