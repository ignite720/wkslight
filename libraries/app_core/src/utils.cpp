#include "pch.h"

#if !TARGET_PLATFORM_ANDROID
#include "app_core/utils.h"

std::string utils::string::str_repeats(const std::string &s, size_t times) {
    std::string result;
    for (size_t i = 0; i < times; ++i) {
        result += s;
    }
    return result;
}

float utils::sdl::now() {
    return SDL_GetTicks() * 0.001f;
}

SDL_FPoint utils::sdl::to_center_point(const SDL_FRect *rect) {
    return SDL_FPoint { rect->x + rect->w * 0.5f, rect->y + rect->h * 0.5f };
}

SDL_Rect utils::sdl::to_rect(const SDL_FRect *rect) {
    return SDL_Rect { int(rect->x), int(rect->y), int(rect->w), int(rect->h) };
}

bool utils::sdl::color_equals(const SDL_Color &color1, const SDL_Color &color2) {
    return true
        && color1.r == color2.r
        && color1.g == color2.g
        && color1.b == color2.b
        && color1.a == color2.a;
}

void utils::sdl::set_draw_color(SDL_Renderer *renderer, const SDL_Color &color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void utils::sdl::clear_with_color(SDL_Renderer *renderer, const SDL_Color &color) {
    set_draw_color(renderer, color);
    SDL_RenderClear(renderer);
}

void utils::sdl::fill_rect_with_color(SDL_Renderer *renderer, const SDL_FRect *rect, const SDL_Color &color) {
    set_draw_color(renderer, color);

    auto tmp_rect = utils::sdl::to_rect(rect);
    SDL_RenderFillRect(renderer, &tmp_rect);
}
#endif