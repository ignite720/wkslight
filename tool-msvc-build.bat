@echo off
call "tool-msvc-build-project.bat" "Release|x64" "%~dp0build\workspace_light.sln" "%~dp0build\app\app.vcxproj"
pause