@echo off
call "msvc-build-project.bat" "Release|x64" "%~dp0build\wkslight.sln" "%~dp0build\app\app.vcxproj"
pause