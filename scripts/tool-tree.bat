@echo off

cd ..

echo %CD%
dir .
if "%~1"=="" (
    timeout /t 2 > nul
)