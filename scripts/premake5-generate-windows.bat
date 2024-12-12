@echo off
cd ..

premake5 vs2022
start build
if "%~1"=="" (
    timeout /t 2 > nul
)