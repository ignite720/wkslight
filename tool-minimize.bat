@echo off

rd /s /q .git
rd /s /q bin
rd /s /q build
rd /s /q "app-rs\target"

rd /s /q "premake5-modules\android-studio\.github"
rd /s /q "premake5-modules\android-studio\example"
del /a /f /q "premake5-modules\android-studio\premake5"

del /a /f /q /s "libraries\lua\*.git"
del /a /f /q /s "premake5-modules\*.git"

rem del /a /f /q ".gitignore"
rem del /a /f /q ".gitmodules"