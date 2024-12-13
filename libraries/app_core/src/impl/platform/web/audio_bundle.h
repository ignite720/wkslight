#pragma once

struct AudioBundle {
    enum AUDIO_CLIP {
        AUDIO_CLIP_BOUNCE = 0,
        AUDIO_CLIP_CLICK,
        AUDIO_CLIP_HIT,
        AUDIO_CLIP_COUNT,
    };

    void play_bgm() {
        this->bgm->play(-1);
    }

    void play_audio_clip(AUDIO_CLIP which) {
        this->clips[which]->play();
    }

    std::unique_ptr<AudioMusic> bgm;
    std::unique_ptr<AudioClip> clips[AUDIO_CLIP_COUNT];
};