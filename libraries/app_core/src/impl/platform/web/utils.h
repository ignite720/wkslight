#pragma once

namespace utils {
    namespace concepts {
        template<typename T>
        concept is_mix_music = std::is_same_v<T, Mix_Music>;

        template<typename T>
        concept is_mix_chunk = std::is_same_v<T, Mix_Chunk>;
    }

    namespace hash {
        template<typename T>
        void hash_combine(size_t &seed, const T &value) noexcept {
            std::hash<T> hasher;
            seed ^= (hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
        }
    }

    namespace string {
        inline String format(const char *fmt, ...) {
            char buf[1024] = {0};

            va_list args;
            va_start(args, fmt);
            std::vsnprintf(buf, sizeof(buf), fmt, args);
            va_end(args);
            return buf;
        }

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
        struct WebFetchUserData {
            enum USAGE {
                USAGE_GAME_INFO_STATS = 0,
                USAGE_COUNT,
            };

            AppCore *app_core;
            USAGE usage;
            void *data;
            size_t size;
        };

        void web_fetch(const char *url);
        void web_fetch_persist_file_store(const char *url, const void *data, size_t size);
        bool web_fetch_persist_file_load(const char *url, void *data, size_t size, AppCore *app_core, WebFetchUserData::USAGE usage);
        bool web_fetch_persist_file_load_sync(const char *url, void *data, size_t size, AppCore *app_core, WebFetchUserData::USAGE usage);
        void web_fetch_persist_file_delete(const char *url);
    }
}