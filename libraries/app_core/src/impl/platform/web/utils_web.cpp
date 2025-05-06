#include "pch.h"

#include "app_core/utils.h"
#include "app_core/app_core.h"

static constexpr const char *const REQUEST_HEADERS[] = {
    //"Accept", "application/json",
    nullptr
};

static void s_web_fetch_succeeded(emscripten_fetch_t *fetch) {
    const auto symbol = utils::string::str_repeats("=", 98);
    printf("%s>>\n>>> %s: %s, status => %d\n", symbol.c_str(), FUNCTION_NAME, fetch->url, fetch->status);
    
    auto *user_data = static_cast<utils::web::WebFetchUserData *>(fetch->userData);
    if (user_data) {
        if (fetch->status == 200) {
            assert(user_data->size == fetch->numBytes);
            memcpy(user_data->data, fetch->data, fetch->numBytes);
        }

        switch (user_data->usage) {
            case utils::web::WebFetchUserData::USAGE_GAME_INFO_STATS: {
                user_data->app_core->app_info_as_mut().game_info.stats_ready = true;
            } break;
        }
        SAFE_DELETE(user_data);
    }

    if (fetch->data && (fetch->numBytes > 0)) {
        const auto text = std::string { fetch->data, fetch->data + fetch->numBytes };
        printf("%s\n", text.c_str());
    }
    
    printf("<<%s\n\n", symbol.c_str());
    emscripten_fetch_close(fetch);
}

static void s_web_fetch_failed(emscripten_fetch_t *fetch) {
    emscripten_fetch_close(fetch);
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

bool utils::web::web_fetch_persist_file_load(const char *url, void *data, size_t size, AppCore *app_core, WebFetchUserData::USAGE usage) {
    PRINT_FUNCTION_NAME();

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);

    auto *user_data = new WebFetchUserData();
    user_data->app_core = app_core;
    user_data->usage = usage;
    user_data->data = data;
    user_data->size = size;
    
    strcpy(attr.requestMethod, "GET");
    attr.attributes = (EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_PERSIST_FILE);
    attr.onsuccess = s_web_fetch_succeeded;
    attr.onerror = s_web_fetch_failed;
    attr.userData = user_data;
    emscripten_fetch(&attr, url);
    return true;
}

bool utils::web::web_fetch_persist_file_load_sync(const char *url, void *data, size_t size, AppCore *app_core, WebFetchUserData::USAGE usage) {
    PRINT_FUNCTION_NAME();

#if WEB_SYNC_FETCH
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    
    strcpy(attr.requestMethod, "GET");
    attr.attributes = (EMSCRIPTEN_FETCH_LOAD_TO_MEMORY /*| EMSCRIPTEN_FETCH_PERSIST_FILE*/ | EMSCRIPTEN_FETCH_SYNCHRONOUS);

    auto ret = false;
    auto *fetch = emscripten_fetch(&attr, url);
    if (fetch) {
        printf("%s: status => %d\n", FUNCTION_NAME, fetch->status);
        ret = (fetch->status == 200);
        if (ret) {
            assert(size == fetch->numBytes);
            memcpy(data, fetch->data, size);
        }

        emscripten_fetch_close(fetch);
    }

    printf("%s: %d\n", FUNCTION_NAME, ret);
    return ret;
#else
    return utils::web::web_fetch_persist_file_load(url, data, size, app_core, usage);
#endif
}

void utils::web::web_fetch_persist_file_delete(const char *url) {
    PRINT_FUNCTION_NAME();
    
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    
    strcpy(attr.requestMethod, "EM_IDB_DELETE");
    emscripten_fetch(&attr, url);
}