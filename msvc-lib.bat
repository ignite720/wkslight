@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
pushd "bin\x64\Release"
call lib.exe /def:foobar.def /out:foobar.lib /machine:x64
popd
pause