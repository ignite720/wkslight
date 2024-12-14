#pragma once

struct Texture {
    explicit Texture(SDL_Renderer *renderer);
    ~Texture();

    int get_width() const { return m_width; }
    int get_height() const { return m_height; }

    bool load_from_file(const char *path, SDL_bool set_color_key = SDL_TRUE);
    bool load_from_text(TTF_Font *font, const char *text, const SDL_Color &fg_color);

    void set_color_mod(Uint8 r, Uint8 g, Uint8 b);
    void set_alpha_mod(Uint8 value);
    void set_blend_mode(SDL_BlendMode value);

    void render(const SDL_FRect *dst_rect, const SDL_Rect *src_rect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    bool load_from_surface(SDL_Surface *surface, const char *tag, const char *from, SDL_bool set_color_key, Uint8 color_key_r = 0, Uint8 color_key_g = 0xff, Uint8 color_key_b = 0xff);
    void drop();
    
private:
    SDL_Renderer *m_renderer = nullptr;
    
    SDL_Texture *m_raw_texture = nullptr;
    int m_width = 0;
    int m_height = 0;
};