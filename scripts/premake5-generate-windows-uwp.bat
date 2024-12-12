@echo off
cd ..

premake5 vs2022 --target_platform=uwp
start build
timeout /t 2 > nul