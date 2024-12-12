@echo off
msbuild build\workspace_light.sln -nologo -m -p:GenerateAppxPackageOnBuild=false -p:Configuration=Release -p:Platform=x64 -p:Projects="build\app\app.vcxproj"