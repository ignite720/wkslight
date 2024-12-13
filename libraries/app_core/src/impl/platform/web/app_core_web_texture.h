#pragma once

struct Texture {
    explicit Texture(SDL_Renderer *renderer, const char *path);
    ~Texture();

    SDL_Texture * get_raw_texture() const { return m_raw_texture; }

    int get_width() const { return m_width; }
    int get_height() const { return m_height; }

private:
    bool load_from_file(SDL_Renderer *renderer, const char *path);

private:
    SDL_Texture *m_raw_texture = nullptr;
    int m_width = 0;
    int m_height = 0;
};