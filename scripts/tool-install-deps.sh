UNAME=$(uname -s)
if [ "$UNAME" = "Linux" ]; then
    apt-get install libsdl2-dev
    apt-get install libsdl2-image-dev
    apt-get install libsdl2-mixer-dev
    apt-get install libsdl2-net-dev
    apt-get install libsdl2-ttf-dev

    apt-get install alsa-base alsa-utils
elif [ "$OS" = "Darwin" ]; then
    brew install sdl2
    brew install sdl2_image
    brew install sdl2_mixer
    brew install sdl2_net
    brew install sdl2_ttf
fi
