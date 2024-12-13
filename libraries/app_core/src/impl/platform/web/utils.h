#pragma once

namespace utils {
    String str_repeats(const String &s, size_t times);

    SDL_FPoint to_center_point(const SDL_FRect *rect);
    SDL_Rect to_rect(const SDL_FRect *rect);
    void fill_rect_with_color(SDL_Renderer *renderer, const SDL_FRect *rect, const SDL_Color &color);
    void fill_rect_with_texture(SDL_Renderer *m_renderer, const SDL_FRect *rect, SDL_Texture *texture);

    void web_fetch(const String &url);
}