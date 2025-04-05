@echo off

if "%~1"=="" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
) else (
    if "%~1"=="gh-action" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64
    )
)

cd ..

ninja -C build Release
if "%~1"=="" (
    timeout /t 2 > nul
)