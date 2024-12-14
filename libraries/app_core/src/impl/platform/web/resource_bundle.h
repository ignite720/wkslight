#pragma once

struct ResourceBundle {
    enum AUDIO_CLIP {
        AUDIO_CLIP_BOUNCE = 0,
        AUDIO_CLIP_CLICK,
        AUDIO_CLIP_HIT,
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
    }

    void play_bgm() {
        this->bgm->play(-1);
    }

    void play_audio_clip(AUDIO_CLIP which) {
        this->clips[which]->play();
    }

    std::unique_ptr<AudioMusic> bgm;
    std::unique_ptr<AudioClip> clips[AUDIO_CLIP_COUNT];
    std::unique_ptr<Font> fonts[FONT_COUNT];
    std::unique_ptr<Texture> textures[TEXTURE_COUNT];
};