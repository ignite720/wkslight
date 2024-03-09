@echo off
set G_VSFilePath="C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe"
set G_VSTarget=%1
set G_VSSolutionFile=%2
set G_VSProjectFile=%3

echo %G_VSTarget%
echo %G_VSSolutionFile%
echo %G_VSProjectFile%
call %G_VSFilePath% /Build %G_VSTarget% /ProjectConfig %G_VSTarget% /Project %G_VSProjectFile% %G_VSSolutionFile%