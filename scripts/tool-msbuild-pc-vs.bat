@echo off

cd ..

msbuild build\wkslight.sln -nologo -m -p:Configuration=Release -p:Platform=x64 -p:Projects="build\app\app.vcxproj"
msbuild build\wkslight.sln -nologo -m -p:Configuration=Release -p:Platform=x64 -p:Projects="build\tests\tests.vcxproj"