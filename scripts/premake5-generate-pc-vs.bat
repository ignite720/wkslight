@echo off

cd ..
if not "%~1"=="" (
    cd ..
)

premake5 vs2022
if "%~1"=="" (
    timeout /t 2 > nul
    start build
)