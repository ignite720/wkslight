#pragma once

namespace concepts {
    template<typename T>
    concept is_music = std::is_same_v<T, Mix_Music>;

    template<typename T>
    concept is_clip = std::is_same_v<T, Mix_Chunk>;
}