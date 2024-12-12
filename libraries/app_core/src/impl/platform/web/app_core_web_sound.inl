#include <type_traits>

template<typename T>
void Sound<T>::global_pause() {
    Mix_PausedMusic();
    Mix_Pause(-1);
}

template<typename T>
void Sound<T>::global_resume() {
    Mix_ResumeMusic();
    Mix_Resume(-1);
}

template<typename T>
Sound<T>::~Sound() {
    if constexpr std::is_same_v<T, Mix_Music> {
        Mix_FreeMusic(m_data);
    } else if constexpr std::is_same_v<T, Mix_Chunk> {
        Mix_FreeChunk(m_data);
    }
}

template<typename T>
bool Sound<T>::load_from_file(const char *path) {
    if constexpr std::is_same_v<T, Mix_Music> {
        m_data = Mix_LoadMUS(path);
    } else if constexpr std::is_same_v<T, Mix_Chunk> {
        m_data = Mix_LoadWAV(path);
    }

    if (!m_data) {
        printf("%s => Failed to load: %s\n", FUNCTION_NAME, Mix_GetError());
        return false;
    }

    printf("%s => Sound loaded successfully: %s\n", FUNCTION_NAME, path);
    return true;
}

template<typename T>
void Sound<T>::set_volume(float value) const {
    auto volume = static_cast<int>(value * MIX_MAX_VOLUME);
    if constexpr std::is_same_v<T, Mix_Music> {
        Mix_VolumeMusic(volume);
    } else if constexpr std::is_same_v<T, Mix_Chunk> {
        Mix_VolumeChunk(m_data, volume);
    }
}

template<typename T>
void Sound<T>::play(int loops) const {
    if constexpr std::is_same_v<T, Mix_Music> {
        Mix_PlayMusic(m_data, loops);
    } else if constexpr std::is_same_v<T, Mix_Chunk> {
        m_channel = Mix_PlayChannel(-1, m_data, loops);
    }
}

template<typename T>
void Sound<T>::stop() const {
    if constexpr std::is_same_v<T, Mix_Music> {
        Mix_HaltMusic();
    } else if constexpr std::is_same_v<T, Mix_Chunk> {
        Mix_HaltChannel(m_channel);
    }
}