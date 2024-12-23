#pragma once

namespace utils {
    namespace concepts {
        template<typename T>
        concept is_audio_music = std::is_same_v<T, AudioMusic>;

        template<typename T>
        concept is_audio_clip = std::is_same_v<T, AudioClip>;

        template<typename T>
        concept is_font = std::is_same_v<T, Font>;
    }
}

class ResourceBundle : public WebObject {
public:
    enum AUDIO_MUSIC {
        AUDIO_MUSIC_INSERT_COIN = 0,
        AUDIO_MUSIC_ITEM_SHOP,
        AUDIO_MUSIC_COUNT,
    };

    enum AUDIO_CLIP {
        AUDIO_CLIP_BOUNCE = 0,
        AUDIO_CLIP_COIN,
        AUDIO_CLIP_HIT,
        AUDIO_CLIP_LOSE,
        AUDIO_CLIP_NEW_RECORD,
        AUDIO_CLIP_COUNT,
    };

    enum FONT {
        FONT_PRESS_START_2P = 0,
        FONT_COUNT,
    };

    explicit ResourceBundle(AppCore *app_core) : WebObject(app_core) {}

public:
    template<typename E, typename T>
    std::enable_if_t<std::is_enum_v<E>, void> put(E index, std::unique_ptr<T> value) {
        if constexpr (utils::concepts::is_audio_music<T>) {
            static_assert(std::is_same_v<E, AUDIO_MUSIC>);

            m_musics[index] = std::move(value);
        } else if constexpr (utils::concepts::is_audio_clip<T>) {
            static_assert(std::is_same_v<E, AUDIO_CLIP>);

            m_clips[index] = std::move(value);
        } else if constexpr (utils::concepts::is_font<T>) {
            static_assert(std::is_same_v<E, FONT>);

            m_fonts[index] = std::move(value);
        }
    }

    void play_audio_music(AUDIO_MUSIC index) {
        m_musics[index]->play(-1);
    }

    void play_audio_clip(AUDIO_CLIP index) {
        m_clips[index]->play();
    }

    bool text_size(FONT font, const String &text, int *w, int *h) {
        return m_fonts[font]->text_size(text.c_str(), w, h);
    }

    SDL_FRect draw_text(FONT font, const String &text, float scale = 1.0f, float x = 0.0f, float y = 0.0f, const SDL_FPoint &anchor = consts::anchor_point::LEFT_TOP, const SDL_Color &color = consts::colors::WHITE) {
        auto *texture = this->get_or_bake_text_texture(font, text, color);
        return this->draw_texture(texture, scale, x, y, anchor);
    }

private:
    size_t text_texture_hash(FONT font, const String &text, const SDL_Color &color) const noexcept {
        size_t hash = 0;
        utils::hash::hash_combine(hash, font);
        utils::hash::hash_combine(hash, text);
        utils::hash::hash_combine(hash, color.r);
        utils::hash::hash_combine(hash, color.g);
        utils::hash::hash_combine(hash, color.b);
        utils::hash::hash_combine(hash, color.a);
        return hash;
    }

    Texture * get_or_bake_text_texture(FONT font, const String &text, const SDL_Color &color) {
        Texture *ptr = nullptr;
        const auto hash = this->text_texture_hash(font, text, color);

        auto iter = m_text_texture_cache.find(hash);
        if (iter != m_text_texture_cache.end()) {
            ptr = iter->second.get();
        } else {
            auto &texture = m_text_texture_cache[hash];
            texture = std::make_unique<Texture>(this->app_core_as_mut_ptr());
            
            auto ret = texture->load_from_text(m_fonts[font].get(), text.c_str(), color);
            if (ret) {
                texture->set_blend_mode(SDL_BLENDMODE_BLEND);
            }
            
            if (this->app_core_as_ptr()->app_info_as_ref().config.logger_verbose) {
                printf("Text texture[%zu] baked %ssuccessfully.\n", m_text_texture_cache.size(), ret ? "" : "un");
            }
            ptr = texture.get();
        }
        return ptr;
    }
    
    SDL_FRect draw_texture(Texture *texture, float scale, float x, float y, const SDL_FPoint &anchor) const {
        const auto w = (texture->get_width() * scale);
        const auto h = (texture->get_height() * scale);
        x = (x - anchor.x * w);
        y = (y - anchor.y * h);

        const auto dst_rect = SDL_FRect { x, y, w, h };
        texture->render(&dst_rect);
        return dst_rect;
    }

private:
    std::unique_ptr<AudioMusic> m_musics[AUDIO_MUSIC_COUNT];
    std::unique_ptr<AudioClip> m_clips[AUDIO_CLIP_COUNT];
    std::unique_ptr<Font> m_fonts[FONT_COUNT];

    collections::HashMap<size_t, std::unique_ptr<Texture>> m_text_texture_cache;
};