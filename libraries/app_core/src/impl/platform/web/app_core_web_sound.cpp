#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Sound::~Sound() {
    Mix_FreeChunk(m_sound);
}

bool Sound::load_from_file(const char *path) {
    m_sound = Mix_LoadWAV(path);
    if (!m_sound) {
        printf("%s => Failed to load: %s\n", FUNCTION_NAME, Mix_GetError());
        return false;
    }

    printf("%s => Sound loaded successfully: %s\n", FUNCTION_NAME, path);
    return true;
}

void Sound::play(int loops) const {
    Mix_PlayChannel(-1, m_sound, loops);
}

#endif