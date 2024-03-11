@echo off

rd /s /q .git
rd /s /q bin
rd /s /q build
rd /s /q "app-rs\target"

rd /s /q "premake5-modules\android-studio\.github"
rd /s /q "premake5-modules\android-studio\example"
del /a /f /q "premake5-modules\android-studio\premake5"