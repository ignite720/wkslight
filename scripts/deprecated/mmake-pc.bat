@echo off

pushd ..\..\build
mingw32-make config=release_x64
popd