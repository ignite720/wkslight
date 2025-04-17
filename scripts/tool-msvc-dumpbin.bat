@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

pushd ..\bin\target\x64\Release
call dumpbin.exe /exports foo.dll >foo-dump.def
rem call dumpbin.exe /LINKERMEMBER foo-dump.lib
popd

pause