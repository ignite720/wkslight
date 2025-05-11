@echo off

cd ..
if "%~1"=="dummy" (
    cd ..
)

premake5 vs2022 --pc_deploy_assets
if "%~1"=="" (
    timeout /t 2 > nul
    start build
)