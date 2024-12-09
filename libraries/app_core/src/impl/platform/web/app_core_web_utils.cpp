#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

static constexpr const char *const REQUEST_HEADERS[] = {
    //"Accept", "application/json",
    nullptr
};

static void s_web_fetch_succeeded(emscripten_fetch_t *fetch) {
    auto symbol = utils::str_repeats("=", 98);
    auto text = String { fetch->data, fetch->data + fetch->numBytes };
    printf("%s>>\nweb_fetch: %s\n%s\n<<%s\n\n", symbol.c_str(), fetch->url, text.c_str(), symbol.c_str());
    
    emscripten_fetch_close(fetch);
}

static void s_web_fetch_failed(emscripten_fetch_t *fetch) {
    emscripten_fetch_close(fetch);
}

String utils::str_repeats(const String &s, size_t times) {
    String result;
    for (size_t i = 0; i < times; ++i) {
        result += s;
    }
    return result;
}

void utils::fill_rect_with_color(SDL_Renderer *renderer, const SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, rect);
}

void utils::fill_rect_with_texture(SDL_Renderer *m_renderer, const SDL_Rect *rect, SDL_Texture *texture) {
    SDL_RenderCopy(m_renderer, texture, nullptr, rect);
}

void utils::web_fetch(const String &url) {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    
    strcpy(attr.requestMethod, "GET");
    attr.attributes = (EMSCRIPTEN_FETCH_LOAD_TO_MEMORY/*| EMSCRIPTEN_FETCH_WAITABLE*/);
    attr.onsuccess = s_web_fetch_succeeded;
    attr.onerror = s_web_fetch_failed;
    attr.requestHeaders = REQUEST_HEADERS;
    //attr.userData = this;
    emscripten_fetch(&attr, url.c_str());
}

#endif