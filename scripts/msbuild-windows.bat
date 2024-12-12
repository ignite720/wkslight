@echo off
cd ..

msbuild build\workspace_light.sln -nologo -m -p:Configuration=Release -p:Platform=x64 -p:Projects="build\app\app.vcxproj"