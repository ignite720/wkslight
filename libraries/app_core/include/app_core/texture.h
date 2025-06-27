#pragma once

#include "app_core/app_core_obj.h"

class ImageSurface {
public:
    ImageSurface() = default;
    explicit ImageSurface(SDL_Surface *surface) { this->set_surface(surface); }
    ImageSurface(const ImageSurface &other) { this->operator=(other); }
    ImageSurface(ImageSurface &&other) noexcept { this->operator=(std::move(other)); }
    ~ImageSurface() {
        this->drop();
    }

public:
    explicit operator bool() const noexcept { return m_surface; }
    ImageSurface & operator=(const ImageSurface &rhs) {
        if (this != &rhs) {
            this->set_surface(rhs.clone_surface());
        }
        return *this;
    }
    ImageSurface & operator=(ImageSurface &&rhs) noexcept {
        if (this != &rhs) {
            this->set_surface(rhs.surface_as_mut_ptr());
            rhs.set_surface(nullptr, false);
        }
        return *this;
    }

    SDL_Surface * surface_as_mut_ptr() { return m_surface; }
    void set_surface(SDL_Surface *value, bool drop_res = true) {
        if (drop_res) {
            this->drop();
        }
        
        assert(!m_surface);
        m_surface = value;
    }

public:
    void drop() {
        if (m_surface) {
            SDL_FreeSurface(m_surface);
            m_surface = nullptr;
        }
    }

    SDL_Surface * clone_surface() const {
        return SDL_ConvertSurface(m_surface, m_surface->format, 0);
    }

    bool load_from_file(const char *path) {
        auto *surface = IMG_Load(path);
        if (!surface) {
            printf("%s => Failed to load Image[%s]: %s\n", FUNCTION_NAME, path, IMG_GetError());
            return false;
        }

        this->set_surface(surface);
        return true;
    }

private:
    SDL_Surface *m_surface = nullptr;
};

class Texture : public AppCoreObj {
public:
    explicit Texture(AppCore &app_core);
    ~Texture();

public:
    int get_width() const { return m_width; }
    int get_height() const { return m_height; }

public:
    bool load_from_file(const char *path, SDL_bool set_color_key = SDL_FALSE);
    bool load_from_text(Font2 *font, const char *text, const SDL_Color &fg_color, Uint32 wrap_length = 0);

    void set_color_mod(Uint8 r, Uint8 g, Uint8 b);
    void set_alpha_mod(Uint8 value);
    void set_blend_mode(SDL_BlendMode value);

    void render(const SDL_FRect *dst_rect, const SDL_FRect *src_rect = nullptr, float angle = 0.0f, const SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    bool load_from_surface(SDL_Surface *surface, const char *tag, const char *from, SDL_bool set_color_key, Uint8 color_key_r = 0, Uint8 color_key_g = 0xff, Uint8 color_key_b = 0xff);
    void drop();
    
private:
    SDL_Texture *m_texture = nullptr;
    int m_width = 0;
    int m_height = 0;
};