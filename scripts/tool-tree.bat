@echo off

cd ..

echo %CD%
dir .
tree .
if "%~1"=="" (
    timeout /t 2 > nul
)