#pragma once

template<typename T>
struct Audio {
    ~Audio();

    static void global_pause();
    static void global_resume();

    bool load_from_file(const char *path);
    void set_volume(float value) const;
    void play(int loops = 0) const;
    void stop() const;

private:
    T *m_data = nullptr;
    int m_channel = -1;
};

using AudioBGM = Audio<Mix_Music>;
using AudioClip = Audio<Mix_Chunk>;

namespace audio {
    template<typename T>
    concept is_music = std::is_same_v<T, Mix_Music>;

    template<typename T>
    concept is_clip = std::is_same_v<T, Mix_Chunk>;
}

#include "app_core_web_audio.inl"