@echo off
setlocal

echo deps/glm: Creating a symbolic links to the folders...
mkdir %~dp0\glm\include
mklink /D %~dp0\glm\include\glm %~dp0\glm\glm
