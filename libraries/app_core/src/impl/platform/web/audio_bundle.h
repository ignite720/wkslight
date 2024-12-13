#pragma once

struct AudioBundle {
    std::unique_ptr<AudioMusic> bgm;
    std::unique_ptr<AudioClip> bounce;
    std::unique_ptr<AudioClip> click;
    std::unique_ptr<AudioClip> hit;
};