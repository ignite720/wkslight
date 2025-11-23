@echo off

premake5 --file=tool-install-deps.lua
call tool-install-deps-sdl2.bat