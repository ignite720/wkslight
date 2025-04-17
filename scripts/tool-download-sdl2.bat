@echo off

cd ..

set SDL2_DIST_VERSION=2.32.4
set SDL2_IMAGE_DIST_VERSION=2.8.8
set SDL2_MIXER_DIST_VERSION=2.8.1
set SDL2_NET_DIST_VERSION=2.2.0
set SDL2_TTF_DIST_VERSION=2.24.0

set SDL2_DIST_FILENAME=SDL2-devel-%SDL2_DIST_VERSION%-VC.zip
set SDL2_IMAGE_DIST_FILENAME=SDL2_image-devel-%SDL2_IMAGE_DIST_VERSION%-VC.zip
set SDL2_MIXER_DIST_FILENAME=SDL2_mixer-devel-%SDL2_MIXER_DIST_VERSION%-VC.zip
set SDL2_NET_DIST_FILENAME=SDL2_net-devel-%SDL2_NET_DIST_VERSION%-VC.zip
set SDL2_TTF_DIST_FILENAME=SDL2_ttf-devel-%SDL2_TTF_DIST_VERSION%-VC.zip

set BIN_DIR=bin
set OUT_DIR=opt

mkdir %BIN_DIR%
pushd %BIN_DIR%
curl -LO https://github.com/libsdl-org/SDL/releases/download/release-%SDL2_DIST_VERSION%/%SDL2_DIST_FILENAME%
curl -LO https://github.com/libsdl-org/SDL_image/releases/download/release-%SDL2_IMAGE_DIST_VERSION%/%SDL2_IMAGE_DIST_FILENAME%
curl -LO https://github.com/libsdl-org/SDL_mixer/releases/download/release-%SDL2_MIXER_DIST_VERSION%/%SDL2_MIXER_DIST_FILENAME%
curl -LO https://github.com/libsdl-org/SDL_net/releases/download/release-%SDL2_NET_DIST_VERSION%/%SDL2_NET_DIST_FILENAME%
curl -LO https://github.com/libsdl-org/SDL_ttf/releases/download/release-%SDL2_TTF_DIST_VERSION%/%SDL2_TTF_DIST_FILENAME%

mkdir %OUT_DIR%
rem tar -xf SDL2-devel-2.32.4-VC.zip -C %OUT_DIR%

powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_DIST_FILENAME% -DestinationPath %OUT_DIR%"
powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_IMAGE_DIST_FILENAME% -DestinationPath %OUT_DIR%"
powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_MIXER_DIST_FILENAME% -DestinationPath %OUT_DIR%"
powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_NET_DIST_FILENAME% -DestinationPath %OUT_DIR%"
powershell -Command "Expand-Archive -Force -LiteralPath %SDL2_TTF_DIST_FILENAME% -DestinationPath %OUT_DIR%"

popd