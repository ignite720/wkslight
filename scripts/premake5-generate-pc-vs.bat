@echo off

cd ..
if "%~1"=="rebuild_me" (
    cd ..
)
if "%~1"=="CI" (
    call "scripts/tool-option-handler.bat" "%*"
)

premake5 vs2022 --pc_deploy_assets
if "%~1"=="" (
    timeout /t 2 > nul
    start build
)