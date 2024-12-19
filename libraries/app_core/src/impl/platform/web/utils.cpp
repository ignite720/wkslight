#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

static constexpr const char *const REQUEST_HEADERS[] = {
    //"Accept", "application/json",
    nullptr
};

struct WebFetchUserData {
    void *data = nullptr;
    size_t size = 0;
};

static void s_web_fetch_succeeded(emscripten_fetch_t *fetch) {
    if (fetch->data && (fetch->numBytes > 0)) {
        const auto symbol = utils::string::str_repeats("=", 98);

        auto *user_data = static_cast<WebFetchUserData *>(fetch->userData);
        if (user_data) {
            assert(user_data->size == fetch->numBytes);
            memcpy(user_data->data, fetch->data, fetch->numBytes);
            delete user_data;

            printf("%s>>\nweb_fetch: %s\nfetch status => %d\n<<%s\n\n", symbol.c_str(), fetch->url, fetch->status, symbol.c_str());
        } else {
            const auto text = String { fetch->data, fetch->data + fetch->numBytes };
            printf("%s>>\nweb_fetch: %s\n%s\n<<%s\n\n", symbol.c_str(), fetch->url, text.c_str(), symbol.c_str());
        }
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
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void utils::sdl::fill_rect_with_color(SDL_Renderer *renderer, const SDL_FRect *rect, const SDL_Color &color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

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
    emscripten_fetch(&attr, url);
}

void utils::web::web_fetch_persist_file_store(const char *url, const void *data, size_t size) {
    PRINT_FUNCTION_NAME();

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);

    auto *data_on_heap = static_cast<char *>(malloc(size));
    memcpy(data_on_heap, data, size);
    
    strcpy(attr.requestMethod, "EM_IDB_STORE");
    attr.attributes = (EMSCRIPTEN_FETCH_REPLACE | EMSCRIPTEN_FETCH_PERSIST_FILE);
    attr.requestData = data_on_heap;
    attr.requestDataSize = size;
    attr.onsuccess = s_web_fetch_succeeded;
    attr.onerror = s_web_fetch_failed;
    emscripten_fetch(&attr, url);
}

void utils::web::web_fetch_persist_file_load(const char *url, void *data, size_t size) {
    PRINT_FUNCTION_NAME();

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);

    auto *user_data = new WebFetchUserData();
    user_data->data = data;
    user_data->size = size;
    
    strcpy(attr.requestMethod, "GET");
    attr.attributes = (EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_PERSIST_FILE);
    attr.onsuccess = s_web_fetch_succeeded;
    attr.onerror = s_web_fetch_failed;
    attr.userData = user_data;
    emscripten_fetch(&attr, url);
}

bool utils::web::web_fetch_persist_file_load_sync(const char *url, void *data, size_t size) {
    PRINT_FUNCTION_NAME();

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    
    strcpy(attr.requestMethod, "GET");
    attr.attributes = (EMSCRIPTEN_FETCH_LOAD_TO_MEMORY /*| EMSCRIPTEN_FETCH_PERSIST_FILE*/ | EMSCRIPTEN_FETCH_SYNCHRONOUS);

    auto ret = false;
    auto *fetch = emscripten_fetch(&attr, url);
    if (fetch) {
        printf("%s: fetch status => %d\n", FUNCTION_NAME, fetch->status);
        ret = (fetch->status == 200);
        if (ret) {
            assert(size == fetch->numBytes);
            memcpy(data, fetch->data, size);
        }

        emscripten_fetch_close(fetch);
    }

    printf("%s: %d\n", FUNCTION_NAME, ret);
    return ret;
}

void utils::web::web_fetch_persist_file_delete(const char *url) {
    PRINT_FUNCTION_NAME();
    
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    
    strcpy(attr.requestMethod, "EM_IDB_DELETE");
    emscripten_fetch(&attr, url);
}

#endif