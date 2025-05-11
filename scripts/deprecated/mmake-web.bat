@echo off

pushd ..\..\build
call "mingw32-make.exe" config=release_wasm
popd