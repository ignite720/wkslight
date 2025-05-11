@echo off

cd ..

rd /S /Q .git
rd /S /Q bin
rd /S /Q build

rd /S /Q "app-rs\assets"
rd /S /Q "app-rs\logs"
rd /S /Q "app-rs\target"

del /F /S /Q /A "libraries\*.git"

rd /S /Q "premake5-modules\android-studio\.github"
rd /S /Q "premake5-modules\android-studio\example"
del /F /Q /A "premake5-modules\android-studio\premake5"

rd /S /Q "premake5-modules\ninja\.github"
rd /S /Q "premake5-modules\ninja\tests"

del /F /S /Q /A "premake5-modules\*.git"

rem del /F /Q /A ".gitignore"
rem del /F /Q /A ".gitmodules"