#pragma once

namespace utils {
    String str_repeats(const String &s, size_t times);

    void fill_rect_with_color(SDL_Renderer *renderer, const SDL_Rect *rect, const SDL_Color &color);
    void fill_rect_with_texture(SDL_Renderer *m_renderer, const SDL_Rect *rect, SDL_Texture *texture);

    void web_fetch(const String &url);
}