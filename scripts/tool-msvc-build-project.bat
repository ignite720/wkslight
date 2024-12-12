@echo off
cd ..

call "tool-msvc-build-project-impl.bat" "Release|x64" "%~dp0build\workspace_light.sln" "%~dp0build\app\app.vcxproj"
pause