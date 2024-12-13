#pragma once

template<typename T>
struct Audio {
    explicit Audio(const char *path);
    ~Audio();

    static void global_pause();
    static void global_resume();

    void set_volume(float value) const;
    void play(int loops = 0);
    void stop() const;

private:
    bool load_from_file(const char *path);

private:
    T *m_data = nullptr;
    int m_channel = -1;
};

using AudioMusic = Audio<Mix_Music>;
using AudioClip = Audio<Mix_Chunk>;

#include "audio.inl"