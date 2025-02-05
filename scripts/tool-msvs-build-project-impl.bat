@echo off

set MSVS_DEVENV_PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe"
set MSVS_TARGET=%1
set MSVS_SOLUTION_PATH=%2
set MSVS_PROJECT_PATH=%3

echo %MSVS_TARGET%
echo %MSVS_SOLUTION_PATH%
echo %MSVS_PROJECT_PATH%
call %MSVS_DEVENV_PATH% /Build %MSVS_TARGET% /ProjectConfig %MSVS_TARGET% /Project %MSVS_PROJECT_PATH% %MSVS_SOLUTION_PATH%