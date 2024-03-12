@echo off
pushd build
call "mingw32-make" config=release_wasm
popd