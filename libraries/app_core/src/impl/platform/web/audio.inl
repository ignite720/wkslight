template<typename T>
void Audio<T>::global_pause() {
    Mix_PausedMusic();
    Mix_Pause(-1);
}

template<typename T>
void Audio<T>::global_resume() {
    Mix_ResumeMusic();
    Mix_Resume(-1);
}

template<typename T>
Audio<T>::Audio(const char *path) {
    auto _ret = this->load_from_file(path);
}

template<typename T>
Audio<T>::~Audio() {
    if constexpr (concepts::is_audio_music<T>) {
        Mix_FreeMusic(m_data);
    } else if constexpr (concepts::is_audio_clip<T>) {
        Mix_FreeChunk(m_data);
    }
}

template<typename T>
void Audio<T>::set_volume(float value) const {
    auto volume = static_cast<int>(value * MIX_MAX_VOLUME);
    if constexpr (concepts::is_audio_music<T>) {
        Mix_VolumeMusic(volume);
    } else if constexpr (concepts::is_audio_clip<T>) {
        Mix_VolumeChunk(m_data, volume);
    }
}

template<typename T>
void Audio<T>::play(int loops) {
    if constexpr (concepts::is_audio_music<T>) {
        Mix_FadeInMusic(m_data, loops, 1000);
    } else if constexpr (concepts::is_audio_clip<T>) {
        m_channel = Mix_PlayChannel(-1, m_data, loops);
    }
}

template<typename T>
void Audio<T>::stop() const {
    if constexpr (concepts::is_audio_music<T>) {
        Mix_HaltMusic();
    } else if constexpr (concepts::is_audio_clip<T>) {
        Mix_HaltChannel(m_channel);
    }
}

template<typename T>
bool Audio<T>::load_from_file(const char *path) {
    if constexpr (concepts::is_audio_music<T>) {
        m_data = Mix_LoadMUS(path);
    } else if constexpr (concepts::is_audio_clip<T>) {
        m_data = Mix_LoadWAV(path);
    }

    if (!m_data) {
        printf("%s => Failed to load Audio[%s]: %s\n", FUNCTION_NAME, path, Mix_GetError());
        return false;
    }

    printf("%s => Audio[%s] loaded successfully\n", FUNCTION_NAME, path);
    return true;
}