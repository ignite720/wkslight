@echo off
premake5 vs2022 --target_platform=uwp
timeout /t 2 > nul