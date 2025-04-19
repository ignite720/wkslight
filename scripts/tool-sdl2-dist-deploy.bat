@echo off

cd ..

set SDL2_NAME=SDL2
set SDL2_IMAGE_NAME=SDL2_image
set SDL2_MIXER_NAME=SDL2_mixer
set SDL2_NET_NAME=SDL2_net
set SDL2_TTF_NAME=SDL2_ttf

set SDL2_DIST_VERSION=2.32.4
set SDL2_IMAGE_DIST_VERSION=2.8.8
set SDL2_MIXER_DIST_VERSION=2.8.1
set SDL2_NET_DIST_VERSION=2.2.0
set SDL2_TTF_DIST_VERSION=2.24.0

set SDL2_DEV=devel
set SDL2_ARCH=x64
set SDL2_DIST_SUFFIX=VC.zip

set SDL2_DIST_FILENAME=%SDL2_NAME%-%SDL2_DEV%-%SDL2_DIST_VERSION%-%SDL2_DIST_SUFFIX%
set SDL2_IMAGE_DIST_FILENAME=%SDL2_IMAGE_NAME%-%SDL2_DEV%-%SDL2_IMAGE_DIST_VERSION%-%SDL2_DIST_SUFFIX%
set SDL2_MIXER_DIST_FILENAME=%SDL2_MIXER_NAME%-%SDL2_DEV%-%SDL2_MIXER_DIST_VERSION%-%SDL2_DIST_SUFFIX%
set SDL2_NET_DIST_FILENAME=%SDL2_NET_NAME%-%SDL2_DEV%-%SDL2_NET_DIST_VERSION%-%SDL2_DIST_SUFFIX%
set SDL2_TTF_DIST_FILENAME=%SDL2_TTF_NAME%-%SDL2_DEV%-%SDL2_TTF_DIST_VERSION%-%SDL2_DIST_SUFFIX%

set SDL2_DIST_DIRNAME=%SDL2_NAME%-%SDL2_DIST_VERSION%
set SDL2_IMAGE_DIST_DIRNAME=%SDL2_IMAGE_NAME%-%SDL2_IMAGE_DIST_VERSION%
set SDL2_MIXER_DIST_DIRNAME=%SDL2_MIXER_NAME%-%SDL2_MIXER_DIST_VERSION%
set SDL2_NET_DIST_DIRNAME=%SDL2_NET_NAME%-%SDL2_NET_DIST_VERSION%
set SDL2_TTF_DIST_DIRNAME=%SDL2_TTF_NAME%-%SDL2_TTF_DIST_VERSION%

set BIN_DIRNAME=bin
set TARGET_DIRNAME=target/%SDL2_ARCH%/Release
set OUT_DIRNAME=opt

mkdir %BIN_DIRNAME%
pushd %BIN_DIRNAME%

if "%~1"=="download" (
    curl -LO https://github.com/libsdl-org/SDL/releases/download/release-%SDL2_DIST_VERSION%/%SDL2_DIST_FILENAME%
    curl -LO https://github.com/libsdl-org/SDL_image/releases/download/release-%SDL2_IMAGE_DIST_VERSION%/%SDL2_IMAGE_DIST_FILENAME%
    curl -LO https://github.com/libsdl-org/SDL_mixer/releases/download/release-%SDL2_MIXER_DIST_VERSION%/%SDL2_MIXER_DIST_FILENAME%
    curl -LO https://github.com/libsdl-org/SDL_net/releases/download/release-%SDL2_NET_DIST_VERSION%/%SDL2_NET_DIST_FILENAME%
    curl -LO https://github.com/libsdl-org/SDL_ttf/releases/download/release-%SDL2_TTF_DIST_VERSION%/%SDL2_TTF_DIST_FILENAME%

    mkdir %OUT_DIRNAME%
    rem tar -xf %SDL2_DIST_FILENAME% -C %OUT_DIRNAME%

    powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_DIST_FILENAME% -DestinationPath %OUT_DIRNAME%"
    powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_IMAGE_DIST_FILENAME% -DestinationPath %OUT_DIRNAME%"
    powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_MIXER_DIST_FILENAME% -DestinationPath %OUT_DIRNAME%"
    powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_NET_DIST_FILENAME% -DestinationPath %OUT_DIRNAME%"
    powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_TTF_DIST_FILENAME% -DestinationPath %OUT_DIRNAME%"
)

xcopy "%OUT_DIRNAME%\%SDL2_DIST_DIRNAME%\lib\%SDL2_ARCH%\*.dll" "%TARGET_DIRNAME%" /I /Y
xcopy "%OUT_DIRNAME%\%SDL2_IMAGE_DIST_DIRNAME%\lib\%SDL2_ARCH%\*.dll" "%TARGET_DIRNAME%" /I /Y
xcopy "%OUT_DIRNAME%\%SDL2_MIXER_DIST_DIRNAME%\lib\%SDL2_ARCH%\*.dll" "%TARGET_DIRNAME%" /I /Y
xcopy "%OUT_DIRNAME%\%SDL2_NET_DIST_DIRNAME%\lib\%SDL2_ARCH%\*.dll" "%TARGET_DIRNAME%" /I /Y
xcopy "%OUT_DIRNAME%\%SDL2_TTF_DIST_DIRNAME%\lib\%SDL2_ARCH%\*.dll" "%TARGET_DIRNAME%" /I /Y

popd