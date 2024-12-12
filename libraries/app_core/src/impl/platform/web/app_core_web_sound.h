#pragma once

template<typename T>
struct Sound {
    ~Sound();

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

#include "app_core_web_sound.inl"