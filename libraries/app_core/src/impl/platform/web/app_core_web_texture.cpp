#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Texture::~Texture() {
    SDL_DestroyTexture(m_raw_texture);
}

bool Texture::load_from_file(SDL_Renderer *renderer, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("%s => Failed to load: %s\n", FUNCTION_NAME, IMG_GetError());
        return false;
    }

    printf("%s => Image loaded successfully: %s\n", FUNCTION_NAME, path);
    m_raw_texture = SDL_CreateTextureFromSurface(renderer, surface);
    m_width = surface->w;
    m_height = surface->h;
    SDL_FreeSurface(surface);
    return true;
}

#endif