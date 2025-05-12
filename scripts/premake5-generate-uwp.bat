@echo off

cd ..
if "%~1"=="rebuild_me" (
    cd ..
)

premake5 vs2022 --target_platform=uwp
if "%~1"=="" (
    timeout /t 2 > nul
    start build
)