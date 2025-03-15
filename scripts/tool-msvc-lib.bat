@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

pushd ..\bin\target\x64\Release
call lib.exe /def:foo-dump.def /out:foo-dump.lib /machine:x64
popd

pause