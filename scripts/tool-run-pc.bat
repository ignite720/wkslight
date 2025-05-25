@echo off

cd ..

pushd "bin/target/x64/Release"
.\app %~1
popd

timeout /t 2 > nul