#pragma once

#if 0
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
#endif

struct ResourceBundle {
    enum BGM {
        BGM_INSERT_COIN = 0,
        BGM_ITEM_SHOP,
        BGM_COUNT,
    };

    enum AUDIO_CLIP {
        AUDIO_CLIP_BOUNCE = 0,
        AUDIO_CLIP_COIN,
        AUDIO_CLIP_HIT,
        AUDIO_CLIP_LOSE,
        AUDIO_CLIP_COUNT,
    };

    enum FONT {
        FONT_PRESS_START_2P = 0,
        FONT_COUNT,
    };

    template<typename T>
    void put(int index, std::unique_ptr<T> value) {
        if constexpr (utils::concepts::is_audio_music<T>) {
            m_bgms[index] = std::move(value);
        } else if constexpr (utils::concepts::is_audio_clip<T>) {
            m_clips[index] = std::move(value);
        } else if constexpr (utils::concepts::is_font<T>) {
            m_fonts[index] = std::move(value);
        }
    }

    void play_bgm(BGM index) {
        m_bgms[index]->play(-1);
    }

    void play_audio_clip(AUDIO_CLIP index) {
        m_clips[index]->play();
    }

    void draw_text(AppCore *app_core, FONT font, const String &text, float scale = 1.0f, float x = 0.0f, float y = 0.0f, const SDL_FPoint &anchor = consts::anchor_point::LEFT_TOP, const SDL_Color &color = consts::colors::WHITE) {
        auto *texture = this->try_bake_text_texture(app_core, font, text, color);
        this->draw_texture(texture, scale, x, y, anchor);
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

    Texture * try_bake_text_texture(AppCore *app_core, FONT font, const String &text, const SDL_Color &color) {
        Texture *ptr = nullptr;
        const auto hash = this->text_texture_hash(font, text, color);

        auto iter = m_text_textures.find(hash);
        if (iter == m_text_textures.end()) {
            ptr = iter->second.get();
        } else {
            auto &texture = m_text_textures[hash];
            texture = std::make_unique<Texture>(app_core);

            auto _ret = texture->load_from_text(m_fonts[font]->get_raw_handle(), text.c_str(), color);
            texture->set_blend_mode(SDL_BLENDMODE_BLEND);

            printf("Text texture[%zu] baked successfully.\n", m_text_textures.size());
            ptr = texture.get();
        }
        return ptr;
    }

    void draw_texture(const Texture *texture, float scale, float x, float y, const SDL_FPoint &anchor) const {
        const auto w = (texture->get_width() * scale);
        const auto h = (texture->get_height() * scale);
        x = (x - anchor.x * w);
        y = (y - anchor.y * h);

        const auto dst_rect = SDL_FRect { x, y, w, h };
        texture->render(&dst_rect);
    }

private:
    std::unique_ptr<AudioMusic> m_bgms[BGM_COUNT];
    std::unique_ptr<AudioClip> m_clips[AUDIO_CLIP_COUNT];
    std::unique_ptr<Font> m_fonts[FONT_COUNT];
    collections::HashMap<size_t, std::unique_ptr<Texture>> m_text_textures;
};