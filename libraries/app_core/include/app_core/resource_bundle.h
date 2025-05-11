#pragma once

#include "app_core/app_core_obj.h"
#include "app_core/audio.h"

namespace utils {
    namespace concepts {
        template<typename T>
        concept is_audio_music = std::is_same_v<T, AudioMusic>;

        template<typename T>
        concept is_audio_clip = std::is_same_v<T, AudioClip>;

        template<typename T>
        concept is_font2 = std::is_same_v<T, Font2>;
    }
}

class ResourceBundle : public AppCoreObj {
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

    struct TextTextureInfo {
        FONT font;
        SDL_Color color;
        std::string text;
    };

    struct TextTextureInfoHash {
        size_t operator()(const TextTextureInfo &value) const noexcept {
            size_t hash = 0;
            utils::hash::hash_combine(hash, value.font);
            utils::hash::hash_combine(hash, value.text);
            utils::hash::hash_combine(hash, value.color.r);
            utils::hash::hash_combine(hash, value.color.g);
            utils::hash::hash_combine(hash, value.color.b);
            utils::hash::hash_combine(hash, value.color.a);
            return hash;
        }
    };

    struct TextTextureInfoEqual {
        bool operator()(const TextTextureInfo &lhs, const TextTextureInfo &rhs) const noexcept {
            //return memcmp(&lhs, &rhs, sizeof(lhs.font) + sizeof(lhs.color)) == 0 && lhs.text == rhs.text;
            return true
                && lhs.font == rhs.font
                && utils::sdl::color_equals(lhs.color, rhs.color)
                && lhs.text == rhs.text;
        }
    };

    explicit ResourceBundle(AppCore &app_core);

public:
    template<typename T, typename E, typename ...Args>
    std::enable_if_t<std::is_enum_v<E>, T *> put(E index, Args &&...args) {
        #if 0
        auto value = std::make_unique<T>(std::forward<Args>(args)...);
        #else
        std::unique_ptr<T> value(new T(std::forward<Args>(args)...));
        #endif
        auto *raw_ptr = value.get();

        if constexpr (utils::concepts::is_audio_music<T>) {
            static_assert(std::is_same_v<E, AUDIO_MUSIC>);
            assert(!m_musics[index]);

            m_musics[index] = std::move(value);
        } else if constexpr (utils::concepts::is_audio_clip<T>) {
            static_assert(std::is_same_v<E, AUDIO_CLIP>);
            assert(!m_audio_clips[index]);

            m_audio_clips[index] = std::move(value);
        } else if constexpr (utils::concepts::is_font2<T>) {
            static_assert(std::is_same_v<E, FONT>);
            assert(!m_fonts[index]);

            m_fonts[index] = std::move(value);
        }
        return raw_ptr;
    }

    void play_audio_music(AUDIO_MUSIC index);
    void play_audio_clip(AUDIO_CLIP index);

    bool text_size(FONT font, const std::string &text, int *w, int *h);

    SDL_FRect draw_text(
        FONT font,
        const std::string &text,
        float scale = 1.0f,
        float x = 0.0f,
        float y = 0.0f,
        const SDL_FPoint &anchor = consts::anchor_point::LEFT_TOP,
        const SDL_Color &color = consts::colors::WHITE
    );

private:
    Texture * get_or_bake_text_texture(FONT font, const std::string &text, const SDL_Color &color);
    SDL_FRect draw_texture(Texture *texture, float scale, float x, float y, const SDL_FPoint &anchor) const;

private:
    std::unique_ptr<AudioMusic> m_musics[AUDIO_MUSIC_COUNT];
    std::unique_ptr<AudioClip> m_audio_clips[AUDIO_CLIP_COUNT];
    std::unique_ptr<Font2> m_fonts[FONT_COUNT];
    std::unordered_map<TextTextureInfo, std::unique_ptr<Texture>, TextTextureInfoHash, TextTextureInfoEqual> m_text_texture_cache;
};