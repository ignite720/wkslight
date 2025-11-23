source scripts/tool-prelude.sh

echo "xxx: " ${OPTIONS["CI"]}
if [[ ${OPTIONS["CI"]} != "1" ]]; then
    source scripts/premake5-bootstrap.sh
fi
premake5 --file=tool-install-deps.lua

if [[ "${UNAME}" == "Linux" ]]; then
    sudo apt-get install -y libsdl2-dev
    sudo apt-get install -y libsdl2-image-dev
    sudo apt-get install -y libsdl2-mixer-dev
    sudo apt-get install -y libsdl2-net-dev
    sudo apt-get install -y libsdl2-ttf-dev

    sudo apt-get install -y alsa-base alsa-utils

    ls -lah /usr/include
elif [[ "${UNAME}" == "Darwin" ]]; then
    brew install sdl2
    brew install sdl2_image
    brew install sdl2_mixer
    brew install sdl2_net
    brew install sdl2_ttf
    
    brew --prefix
    echo ${HOMEBREW_PREFIX}
    ls -lah /usr/local/Cellar
fi
