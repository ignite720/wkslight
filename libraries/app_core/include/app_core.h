#pragma once

#include <foo.h>
#include <simplerand/simplerand.hpp>

#include "app_core_api.h"

extern "C" {
    APP_CORE_API int app_core_startup();
}

struct APP_CORE_API Vector2 {
    static float length(const Vector2 &v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    static Vector2 normalize(const Vector2 &v) {
        const float len = Vector2::length(v);

        Vector2 ret = v;
        if (len != 0.0f) {
            ret.x /= len;
            ret.y /= len;
        }
        return ret;
    }

    float x = 0.0f;
    float y = 0.0f;
};

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
            bool paddle_friction = false;

            struct Stats {
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

    virtual void restart() {}
    virtual void * renderer_as_void_p() { return nullptr; }
    virtual void update_app_info() {}

    virtual void play_bgm(int index) const {}
    virtual void play_audio_clip(int index) const {}

public:
    const AppInfo & app_info_as_ref() const { return m_app_info; }
    AppInfo & app_info_as_mut() { return m_app_info; }

protected:
    AppInfo m_app_info;
};