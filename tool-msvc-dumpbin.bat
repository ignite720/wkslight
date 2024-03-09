@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
pushd "bin\x64\Release"
call dumpbin.exe /exports foo.dll >foobar.def
rem call dumpbin.exe /LINKERMEMBER foobar.lib
popd
pause