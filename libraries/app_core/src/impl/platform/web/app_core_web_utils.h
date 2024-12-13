#pragma once

namespace utils {
    namespace random {
        void init_seed(unsigned seed = 0) {
            srand(seed != 0 ? seed : static_cast<unsigned>(time(nullptr)));
        }

        inline float gen() {
            return rand() / float(RAND_MAX);
        }

        template<typename T>
        T gen_range(T min_value, T max_value) {
            return static_cast<T>(gen() * (max_value - min_value) + min_value);
        }
    }

    String str_repeats(const String &s, size_t times);

    SDL_Rect to_rect(const SDL_FRect *rect);
    void fill_rect_with_color(SDL_Renderer *renderer, const SDL_FRect *rect, const SDL_Color &color);
    void fill_rect_with_texture(SDL_Renderer *m_renderer, const SDL_FRect *rect, SDL_Texture *texture);

    void web_fetch(const String &url);
}