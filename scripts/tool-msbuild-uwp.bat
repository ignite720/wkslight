@echo off

cd ..

msbuild build\wkslight.sln -nologo -m -p:GenerateAppxPackageOnBuild=false -p:Configuration=Release -p:Platform=x64 -p:Projects="build\app\app.vcxproj"