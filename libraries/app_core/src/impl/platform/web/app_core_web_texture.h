#pragma once

struct Texture {
    ~Texture();

    bool load_from_file(SDL_Renderer *renderer, const char *path);

    SDL_Texture * get_raw_texture() const { return m_raw_texture; }

    int get_width() const { return m_width; }
    int get_height() const { return m_height; }

private:
    SDL_Texture *m_raw_texture = nullptr;
    int m_width = 0;
    int m_height = 0;
};