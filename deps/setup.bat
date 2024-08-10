@echo off
setlocal

echo deps/glm: Creating a symbolic links to the folders...
mkdir %~dp0\glm\include
mklink /D %~dp0\glm\include\glm %~dp0\glm\glm

echo deps/xxHash: Preparing include dir...
mkdir %~dp0\xxHash\include\xxHash
mklink %~dp0\xxHash\include\xxHash\xxhash.h %~dp0\xxHash\xxhash.h
