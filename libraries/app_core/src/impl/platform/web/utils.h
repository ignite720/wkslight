#pragma once

namespace utils {
    template<typename T>
    void hash_combine(size_t &seed, const T &value) noexcept {
        std::hash<T> hasher;
        seed ^= (hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
    }

    namespace string {
        String str_repeats(const String &s, size_t times);
    }

    namespace sdl {
        float now();
        
        SDL_FPoint to_center_point(const SDL_FRect *rect);
        SDL_Rect to_rect(const SDL_FRect *rect);

        void clear_with_color(SDL_Renderer *renderer, const SDL_Color &color);
        void fill_rect_with_color(SDL_Renderer *renderer, const SDL_FRect *rect, const SDL_Color &color);
    }

    namespace web {
        void web_fetch(const String &url);
    }
}