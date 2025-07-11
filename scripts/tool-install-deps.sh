source scripts/tool-prelude.sh

if [[ "${UNAME}" == "Linux" ]]; then
    sudo apt-get install libsdl2-dev
    sudo apt-get install libsdl2-image-dev
    sudo apt-get install libsdl2-mixer-dev
    sudo apt-get install libsdl2-net-dev
    sudo apt-get install libsdl2-ttf-dev

    sudo apt-get install alsa-base alsa-utils

    ls -lah /usr/include
elif [[ "${UNAME}" == "Darwin" ]]; then
    brew install sdl2
    brew install sdl2_image
    brew install sdl2_mixer
    brew install sdl2_net
    brew install sdl2_ttf

    la -lah ${HOMEBREW_PREFIX}/Cellar
fi
