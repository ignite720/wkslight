@echo off

cd ..
if "%~1"=="CI" (
    call "scripts/stool-options-handler.bat" "%*"
)

premake5 ninja --pc_deploy_assets %OPTION_CI%
if "%~1"=="" (
    timeout /t 2 > nul
)