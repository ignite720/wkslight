@echo off

call "tool-msvs-build-project-impl.bat" "Release|x64" "%~dp0..\build\wkslight.sln" "%~dp0..\build\app\app.vcxproj"
pause