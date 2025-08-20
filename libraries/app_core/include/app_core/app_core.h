#pragma once

#include "app_info.h"
#include "input.h"

#include <wkstk/deletion_queue.hpp>

#define APP_CORE_OBJ_GET_RENDERER                               reinterpret_cast<SDL_Renderer *>(this->app_core_as_mut_ptr()->renderer_as_mut_ptr())

#ifdef __cplusplus
extern "C" {
#endif

APP_CORE_API int app_core_startup(int argc, char *argv[]);

APP_CORE_API void app_core_test_bar(void);
APP_CORE_API void app_core_test_baz_qux(void);
APP_CORE_API void app_core_test_enum(void);
APP_CORE_API void app_core_test_foo(void);
APP_CORE_API void app_core_test_json(void);
APP_CORE_API void app_core_test_logging(void);
APP_CORE_API void app_core_test_lua(void);
APP_CORE_API void app_core_test_noise(void);
APP_CORE_API void app_core_test_rtm(void);
APP_CORE_API void app_core_test_stb(void);
APP_CORE_API void app_core_test_xmath(void);

#ifdef __cplusplus
}
#endif

class APP_CORE_API GameObject {
public:
    static std::shared_ptr<GameObject> create() {
        static int s_id_counter = 0;

        auto id = s_id_counter++;
        auto go = std::make_shared<GameObject>(id);
        return go;
    }

public:
    explicit GameObject(int id) : m_id(id) {}

public:
    int get_id() const { return m_id; }

    const std::string & get_name() const { return m_name; }
    void set_name(const std::string &value) { m_name = value; }

private:
    int m_id;
    std::string m_name;
};

#if !TARGET_PLATFORM_ANDROID
class APP_CORE_API AppCore {
public:
    static std::unique_ptr<AppCore> create();
    
private:
    static std::unique_ptr<AppCore> create_android();
    static std::unique_ptr<AppCore> create_pc();
    static std::unique_ptr<AppCore> create_uwp();
    static std::unique_ptr<AppCore> create_web();

public:
    virtual ~AppCore();

    virtual void preload() {}
    virtual int init(const char *title, int width, int height, bool fullscreen, bool linear_filter, int auto_close_secs);
    virtual int run();

    virtual void update();
    virtual void render();
    virtual void render_background();
    virtual void render_foreground();
    virtual void render_imgui();

    virtual void restart();
    virtual void reset_gamesave();
    virtual void update_app_info();

public:
    const AppInfo & app_info_as_ref() const { return m_app_info; }
    AppInfo & app_info_as_mut() { return m_app_info; }
    
    void * renderer_as_mut_ptr() { return m_renderer; }

public:
    void play_audio_music(int index) const;
    void play_audio_clip(int index) const;

private:
    bool init_sdl2();
    bool init_sdl2_libs();
    bool init_imgui();
    bool init_assets();

    void drop();

    void render_imgui_begin();
    void render_imgui_end();

private:
    AppInfo m_app_info;
    wkstk::DeletionQueue m_deletion_queue;

protected:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

private:
    Input m_input;

private:
    ResourceBundle *m_resource_bundle = nullptr;
    Ball *m_ball = nullptr;
    Paddle *m_paddle = nullptr;
};
#endif