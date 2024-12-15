#pragma once

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

    enum TEXTURE {
        TEXTURE_1 = 0,
        TEXTURE_2,
        TEXTURE_3,
        TEXTURE_4,
        TEXTURE_5,
        TEXTURE_6,
        TEXTURE_7,
        TEXTURE_8,
        TEXTURE_COUNT,
    };

    void play_bgm(BGM which) {
        this->bgms[which]->play(-1);
    }

    void play_audio_clip(AUDIO_CLIP which) {
        this->clips[which]->play();
    }

    void bake_text(TEXTURE which, FONT font, const String &text, const SDL_Color &color) {
        auto _ret = this->textures[which]->load_from_text(this->fonts[font]->get_raw_handle(), text.c_str(), color);
        this->textures[which]->set_blend_mode(SDL_BLENDMODE_BLEND);
    }

    void draw_texture(TEXTURE which, float scale, float x, float y, const SDL_FPoint &anchor) {
        const auto w = (this->textures[which]->get_width() * scale);
        const auto h = (this->textures[which]->get_height() * scale);
        x = (x + anchor.x * w);
        y = (y + anchor.y * h);

        const auto dst_rect = SDL_FRect { x, y, w, h };
        this->textures[which]->render(&dst_rect);
    }

    void draw_text(TEXTURE which, FONT font, const String &text, float scale = 1.0f, float x = 0.0f, float y = 0.0f, const SDL_FPoint &anchor = consts::anchor_point::LEFT_TOP, const SDL_Color &color = consts::colors::WHITE) {
        this->bake_text(which, font, text, color);
        this->draw_texture(which, scale, x, y, anchor);
    }

    std::unique_ptr<AudioMusic> bgms[BGM_COUNT];
    std::unique_ptr<AudioClip> clips[AUDIO_CLIP_COUNT];
    std::unique_ptr<Font> fonts[FONT_COUNT];
    std::unique_ptr<Texture> textures[TEXTURE_COUNT];
};