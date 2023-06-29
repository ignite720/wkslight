@echo off
pushd build
call "mingw32-make" config=release_x64
popd