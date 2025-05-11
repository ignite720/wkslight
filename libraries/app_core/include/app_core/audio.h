#pragma once

#include "app_core/utils.h"

template<typename T>
class Audio {
    friend class ResourceBundle;
public:
    static void global_pause();
    static void global_resume();

private:
    explicit Audio(const char *path);
public:
    ~Audio();
    
public:
    void set_volume(float value) const;
    void play(int loops = 0);
    void stop() const;

private:
    bool load_from_file(const char *path);

private:
    T *m_handle = nullptr;
    int m_channel = -1;
};

using AudioMusic = Audio<Mix_Music>;
using AudioClip = Audio<Mix_Chunk>;

#include "audio.inl"