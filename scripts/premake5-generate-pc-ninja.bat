@echo off

cd ..

premake5 ninja --pc_deploy_assets
if "%~1"=="" (
    timeout /t 2 > nul
)