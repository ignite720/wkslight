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
    static std::unique_ptr<AppCore> create();
    
private:
    static std::unique_ptr<AppCore> create_android();
    static std::unique_ptr<AppCore> create_pc();
    static std::unique_ptr<AppCore> create_uwp();
    static std::unique_ptr<AppCore> create_web();

public:
    virtual ~AppCore() = default;

    virtual int init(int width, int height) {
        m_window_width = float(width);
        m_window_height = float(height);

        simplerand::from_seed(static_cast<unsigned>(std::time(nullptr)));
        return 0;
    }

    virtual int run() = 0;

    virtual void update() {}
    virtual void render() {}

    virtual void play_audio_clip(int index) const {}

public:
    float get_window_width() const { return m_window_width; }
    float get_window_height() const { return m_window_height; }

protected:
    float m_window_width = 0.0f;
    float m_window_height = 0.0f;
};