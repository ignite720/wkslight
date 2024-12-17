#pragma once

#include <foo.h>
#include <rtm/math.h>
#include <simplerand/simplerand.hpp>

#include "app_core_api.h"

extern "C" {
    APP_CORE_API int app_core_startup();
}

enum class GfxApi {
    Unknown = 0,
    D3D12,
    Vulkan,
    Count
};

struct APP_CORE_API AppCoreGfx {
    static std::unique_ptr<AppCoreGfx> create(GfxApi api);
    
private:
    static std::unique_ptr<AppCoreGfx> create_d3d12();
    static std::unique_ptr<AppCoreGfx> create_vulkan();

public:
    virtual ~AppCoreGfx() = default;

    virtual void test() const = 0;
};

struct APP_CORE_API AppCore {
    struct AppInfo {
        float window_width = 0.0f;
        float window_height = 0.0f;

        struct Config {
            bool logger_verbose = false;
        } config;
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
            bool paddle_friction = false;

            struct Stats {
                int num_rounds = 1;
                int num_streaks = 0;
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
    virtual void * renderer_as_mut_void_p() { return nullptr; }
    virtual void update_app_info() {}

    virtual void play_bgm(int index) const {}
    virtual void play_audio_clip(int index) const {}

public:
    const AppInfo & app_info_as_ref() const { return m_app_info; }
    AppInfo & app_info_as_mut() { return m_app_info; }

private:
    AppInfo m_app_info;
};