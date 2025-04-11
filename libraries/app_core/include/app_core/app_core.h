#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <foo/foo.h>

#include <mathx/mathx_rtm.h>
using namespace rtm;

#if !defined(__APPLE__)
PRAGMA_WARNING_PUSH
PRAGMA_WARNING_IGNORE_CLANG("-Wattributes")
PRAGMA_WARNING_IGNORE_GCC("-Wattributes")
PRAGMA_WARNING_IGNORE_MSVC(4616)
#include <mathx/mathx_xmath.h>
PRAGMA_WARNING_POP

using namespace XMath;
#endif

#include <simplerand/simplerand.hpp>

#include "app_core/app_core_api.h"
#include "app_core/logging.h"

#ifdef __cplusplus
extern "C" {
#endif

APP_CORE_API int app_core_startup(void);

APP_CORE_API void app_core_test_bar(void);
APP_CORE_API void app_core_test_baz_qux(void);
APP_CORE_API void app_core_test_enum(void);
APP_CORE_API void app_core_test_foo(void);
APP_CORE_API void app_core_test_json(void);
APP_CORE_API void app_core_test_logging(void);
APP_CORE_API void app_core_test_lua(void);
APP_CORE_API void app_core_test_noise(void);
APP_CORE_API void app_core_test_rtm(void);
APP_CORE_API void app_core_test_xmath(void);

#ifdef __cplusplus
}
#endif

class /*APP_CORE_API*/ GameObject {
public:
    static std::shared_ptr<GameObject> create() {
        static int s_id_counter = 0;

        auto id = s_id_counter++;
        auto go = std::make_shared<GameObject>(id);
        return go;
    }

public:
    explicit GameObject(int id) : m_id(id) {
        static int s_id_counter = 0;
        m_id = s_id_counter++;
    }

public:
    int get_id() const { return m_id; }

    const String & get_name() const { return m_name; }
    void set_name(const String &value) { m_name = value; }

private:
    int m_id;
    String m_name;
};

enum class GfxApi {
    Unknown = 0,
    D3D12,
    Vulkan,
    Count
};

class APP_CORE_API AppCoreGfx {
public:
    static std::unique_ptr<AppCoreGfx> create(GfxApi api);
    
private:
    static std::unique_ptr<AppCoreGfx> create_d3d12();
    static std::unique_ptr<AppCoreGfx> create_vulkan();

public:
    virtual ~AppCoreGfx() = default;

    virtual void test() const = 0;
};

class APP_CORE_API AppCore {
public:
    struct AppInfo {
        float window_width = 0.0f;
        float window_height = 0.0f;

        struct Config {
            bool logger_verbose = false;
        } config;
        struct GameSave {
            int high_score = 0;
        } gamesave;
        struct Stats {
            float now = 0.0f;
            float last_time = 0.0f;

            float delta_time = 0.0f;
            int fps = 0;

            struct Staging {
                int frames_accumulated = 0;
                float time_accumulated = 0.0f;
            } staging;
        } stats;
        struct GameInfo {
            bool game_over = true;
            bool stats_ready = false;
            bool paddle_friction = false;

            struct Stats {
                int num_rounds = 0;
                int score = 0;
            } stats;
        } game_info;
    };

    static std::unique_ptr<AppCore> create();
    
private:
    static std::unique_ptr<AppCore> create_android();
    static std::unique_ptr<AppCore> create_pc();
    static std::unique_ptr<AppCore> create_uwp();
    static std::unique_ptr<AppCore> create_web();

public:
    virtual ~AppCore();

    virtual void preload() {}
    virtual int init(int width, int height, bool linear_filter);
    virtual int run();

    virtual void update();
    virtual void render();
    virtual void render_imgui();

    virtual void restart() { m_app_info.game_info.game_over = false; }
    virtual void * renderer_as_mut_ptr() { return nullptr; }
    virtual void update_app_info() {}
    virtual void reset_gamesave() { m_app_info.gamesave = {}; }

    virtual void play_audio_music(int index) const {}
    virtual void play_audio_clip(int index) const {}

public:
    const AppInfo & app_info_as_ref() const { return m_app_info; }
    AppInfo & app_info_as_mut() { return m_app_info; }

private:
    AppInfo m_app_info;

protected:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    
    bool m_quit = false;
    bool m_show_demo_window = false;
};