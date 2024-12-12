@echo off
cd ..

premake5 vs2022
if "%~1"=="" (
    start build
    timeout /t 2 > nul
)