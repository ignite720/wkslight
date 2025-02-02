emcc --version
emcc --show-ports

echo -e '#include <SDL2/SDL.h>\nint main() { SDL_Init(SDL_INIT_VIDEO); SDL_Quit(); return 0; }' > main.c
EMCC_VERBOSE=0 emcc -v main.c -O2 -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS='["bmp", "jpg", "png"]' -sUSE_SDL_MIXER=2 -sUSE_SDL_NET=2 -sUSE_SDL_TTF=2 -o main.js

#EMCC_LOCAL_PORTS=\
#sdl2=/opt/emsdk-ports/sdl2/SDL-release-2.24.2,\
#libpng=/opt/emsdk-ports/libpng/libpng-1.6.39 \
#emcc main.c -O2 -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS='["png"]' -sUSE_SDL_MIXER=2 -sUSE_SDL_NET=2 -sUSE_SDL_TTF=2 -s EXPORTED_FUNCTIONS='["_main"]' --preload-file assets -o main.js

export EMCC_VERBOSE=1