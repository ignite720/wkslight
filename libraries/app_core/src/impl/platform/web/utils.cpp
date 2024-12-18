#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

static constexpr const char *const REQUEST_HEADERS[] = {
    //"Accept", "application/json",
    nullptr
};

static void s_web_fetch_succeeded(emscripten_fetch_t *fetch) {
    if (fetch->data && (fetch->numBytes > 0)) {
        const auto symbol = utils::string::str_repeats("=", 98);
        const auto text = String { fetch->data, fetch->data + fetch->numBytes };
        printf("%s>>\nweb_fetch: %s\n%s\n<<%s\n\n", symbol.c_str(), fetch->url, text.c_str(), symbol.c_str());
    }
    
    emscripten_fetch_close(fetch);
}

static void s_web_fetch_failed(emscripten_fetch_t *fetch) {
    emscripten_fetch_close(fetch);
}

String utils::string::str_repeats(const String &s, size_t times) {
    String result;
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

void utils::sdl::clear_with_color(SDL_Renderer *renderer, const SDL_Color &color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, /*color.a*/0xff);
    SDL_RenderClear(renderer);
}

void utils::sdl::fill_rect_with_color(SDL_Renderer *renderer, const SDL_FRect *rect, const SDL_Color &color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, /*color.a*/0xff);

    auto tmp_rect = utils::sdl::to_rect(rect);
    SDL_RenderFillRect(renderer, &tmp_rect);
}

void utils::web::web_fetch(const char *url) {
    PRINT_FUNCTION_NAME();

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    
    strcpy(attr.requestMethod, "GET");
    attr.attributes = (EMSCRIPTEN_FETCH_LOAD_TO_MEMORY/* | EMSCRIPTEN_FETCH_WAITABLE*/);
    attr.onsuccess = s_web_fetch_succeeded;
    attr.onerror = s_web_fetch_failed;
    attr.requestHeaders = REQUEST_HEADERS;
    //attr.userData = this;
    emscripten_fetch(&attr, url);
}

void utils::web::web_fetch_persist_file_store(const char *url, const void *data, size_t size) {
    PRINT_FUNCTION_NAME();

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    
    strcpy(attr.requestMethod, "EM_IDB_STORE");
    attr.attributes = (EMSCRIPTEN_FETCH_REPLACE | EMSCRIPTEN_FETCH_PERSIST_FILE);
    attr.requestData = reinterpret_cast<const char *>(data);
    attr.requestDataSize = size;
    attr.onsuccess = s_web_fetch_succeeded;
    attr.onerror = s_web_fetch_failed;
    emscripten_fetch(&attr, url);
}

void utils::web::web_fetch_persist_file_load(const char *url, void *data, size_t size) {
    PRINT_FUNCTION_NAME();

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    
    strcpy(attr.requestMethod, "GET");
    attr.attributes = (EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS);
    auto *fetch = emscripten_fetch(&attr, url);
    if (fetch) {
        if (fetch->status == 200) {
            assert(size == fetch->numBytes);
            memcpy(data, fetch->data, size);
        }

        emscripten_fetch_close(fetch);
    }
}

void utils::web::web_fetch_persist_file_delete(const char *url) {
    PRINT_FUNCTION_NAME();
    
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    
    strcpy(attr.requestMethod, "EM_IDB_DELETE");
    emscripten_fetch(&attr, url);
}

#endif