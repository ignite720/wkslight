#include "pch.h"

#if !TARGET_PLATFORM_ANDROID
#include "app_core/resource_bundle.h"
#include "app_core/app_core.h"
#include "app_core/font2.h"
#include "app_core/texture.h"

ResourceBundle::ResourceBundle(AppCore &app_core) : AppCoreObj(app_core) {

}

void ResourceBundle::play_audio_music(AUDIO_MUSIC index) {
    m_musics[index]->play(-1);
}

void ResourceBundle::play_audio_clip(AUDIO_CLIP index) {
    m_audio_clips[index]->play();
}

bool ResourceBundle::text_size(FONT font, const std::string &text, int *w, int *h) {
    return m_fonts[font]->text_size(text.c_str(), w, h);
}

SDL_FRect ResourceBundle::draw_text(
    FONT font,
    const std::string &text,
    float scale,
    float x,
    float y,
    const SDL_FPoint &anchor,
    const SDL_Color &color
) {
    auto *texture = this->get_or_bake_text_texture(font, text, color);
    return this->draw_texture(texture, scale, x, y, anchor);
}

Texture * ResourceBundle::get_or_bake_text_texture(FONT font, const std::string &text, const SDL_Color &color) {
    Texture *ptr = nullptr;
    const auto key = TextTextureInfo { font, color, text };

    auto iter = m_text_texture_cache.find(key);
    if (iter != m_text_texture_cache.end()) {
        ptr = iter->second.get();
    } else {
        auto &texture = m_text_texture_cache[key];
        texture = std::make_unique<Texture>(*this->app_core_as_mut_ptr());
        
        auto ret = texture->load_from_text(m_fonts[font].get(), text.c_str(), color);
        if (ret) {
            texture->set_blend_mode(SDL_BLENDMODE_BLEND);
        }
        
        if (this->app_core_as_ptr()->app_info_as_ref().config.logger_verbose) {
            printf("Text[%s] texture[%zu] baked %ssuccessfully.\n", text.c_str(), m_text_texture_cache.size(), ret ? "" : "un");
        }
        ptr = texture.get();
    }
    return ptr;
}

SDL_FRect ResourceBundle::draw_texture(Texture *texture, float scale, float x, float y, const SDL_FPoint &anchor) const {
    const auto w = (texture->get_width() * scale);
    const auto h = (texture->get_height() * scale);
    x = (x - anchor.x * w);
    y = (y - anchor.y * h);

    const auto dst_rect = SDL_FRect { x, y, w, h };
    texture->render(&dst_rect);
    return dst_rect;
}
#endif