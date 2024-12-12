@echo off
cd ..

premake5 vs2022 --target_platform=uwp
start build
if "%~1"=="" (
    timeout /t 2 > nul
)