#include "pch.h"

#if !TARGET_PLATFORM_ANDROID
#include "app_core/texture.h"
#include "app_core/app_core.h"
#include "app_core/font2.h"
#include "app_core/utils.h"

Texture::Texture(AppCore &app_core)
    : AppCoreObj(app_core) {

}

Texture::~Texture() {
    this->drop();
}

bool Texture::load_from_file(const char *path, SDL_bool set_color_key) {
    this->drop();

    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("%s => Failed to load Image[%s]: %s\n", FUNCTION_NAME, path, IMG_GetError());
        return false;
    }
    return this->load_from_surface(surface, "Image", path, set_color_key);
}

bool Texture::load_from_text(Font2 *font, const char *text, const SDL_Color &fg_color, Uint32 wrap_length) {
    this->drop();
    
    SDL_Surface *surface = font->render_text(text, fg_color, wrap_length);
    if (!surface) {
        printf("%s => Failed to render text surface: %s\n", FUNCTION_NAME, TTF_GetError());
        return false;
    }
    return this->load_from_surface(surface, "Text", text, SDL_FALSE);
}

void Texture::set_color_mod(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetTextureColorMod(m_texture, r, g, b);
}

void Texture::set_alpha_mod(Uint8 value) {
    SDL_SetTextureAlphaMod(m_texture, value);
}

void Texture::set_blend_mode(SDL_BlendMode value) {
    SDL_SetTextureBlendMode(m_texture, value);
}

void Texture::render(const SDL_FRect *dst_rect, const SDL_FRect *src_rect, float angle, const SDL_Point *center, SDL_RendererFlip flip) {
    auto tmp_src_rect = SDL_Rect {};
    auto tmp_dst_rect = utils::sdl::to_rect(dst_rect);
    if (src_rect) {
        tmp_src_rect = utils::sdl::to_rect(dst_rect);

        tmp_dst_rect.w = int(src_rect->w);
        tmp_dst_rect.h = int(src_rect->h);
    }
    SDL_RenderCopyEx(APP_CORE_OBJ_GET_RENDERER, m_texture, src_rect ? &tmp_src_rect : nullptr, &tmp_dst_rect, angle, center, flip);
}

bool Texture::load_from_surface(SDL_Surface *surface, const char *tag, const char *from, SDL_bool set_color_key, Uint8 color_key_r, Uint8 color_key_g, Uint8 color_key_b) {
    auto ret = true;
    if (this->app_core_as_mut_ptr()->app_info_as_ref().config.logger_verbose) {
        printf("%s => %s[%s] loaded successfully.\n", FUNCTION_NAME, tag, from);
    }

    if (set_color_key) {
        SDL_SetColorKey(surface, set_color_key, SDL_MapRGB(surface->format, color_key_r, color_key_g, color_key_b));
    }

    m_texture = SDL_CreateTextureFromSurface(APP_CORE_OBJ_GET_RENDERER, surface);
    if (!m_texture) {
        printf("%s => Failed to create texture from %s[%s]: %s\n", FUNCTION_NAME, tag, from, SDL_GetError());
        ret = false;
    }

    m_width = surface->w;
    m_height = surface->h;

    SDL_FreeSurface(surface);
    return ret;
}

void Texture::drop() {
    if (m_texture) {
        SDL_DestroyTexture(m_texture);

        m_texture = nullptr;
    }
}
#endif