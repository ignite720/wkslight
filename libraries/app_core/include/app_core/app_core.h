#pragma once

#include <foo/foo.h>
#include <simplerand/simplerand.hpp>

#include "app_core/logging.h"

#include "app_core/math_rtm.h"
using namespace rtm;

#if !defined(__APPLE__)
#include "app_core/math_xmath.h"
using namespace XMath;
#endif

#include "app_core/app_core_api.h"

extern "C" {
    APP_CORE_API int app_core_startup();
}

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
    virtual ~AppCore() = default;

    virtual void preload() {}
    virtual int init(int width, int height, bool linear_filter) {
        m_app_info.window_width = float(width);
        m_app_info.window_height = float(height);

        simplerand::from_seed(static_cast<unsigned>(std::time(nullptr)));
        return 0;
    }

    virtual int run() = 0;

    virtual void update() {}
    virtual void render() {}

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
};