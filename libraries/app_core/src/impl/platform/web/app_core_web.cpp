#include "pch.h"

#include "app_core/app_core.h"
#include "app_core/utils.h"
#include "net_web.h"

#include <imgui.h>

static void s_main_loop(void *arg) {
    auto *app_core = static_cast<AppCore *>(arg);

    app_core->update();
    app_core->render();
}

class AppCoreWeb : public AppCore {
public:
    ~AppCoreWeb();

    virtual void preload() override;
    virtual int init(int width, int height, bool linear_filter, int auto_close_secs) override;
    virtual int run() override;

    virtual void render_imgui() override;

    virtual void update_app_info() override;
    virtual void reset_gamesave() override;

private:
    std::unique_ptr<Net> m_net;
};

AppCoreWeb::~AppCoreWeb() {
    PRINT_FUNCTION_NAME();
}

void AppCoreWeb::preload() {
    PRINT_FUNCTION_NAME();

    utils::web::web_fetch("example.json");
    utils::web::web_fetch("https://httpbin.org/xml");

    auto &gamesave = this->app_info_as_mut().gamesave;
    auto _ret = utils::web::web_fetch_persist_file_load_sync(consts::text::GAMESAVE_FILE_NAME, &gamesave, sizeof(gamesave), this, utils::web::WebFetchUserData::USAGE_GAME_INFO_STATS);
    
    m_net = std::make_unique<NetWeb>(*this);
    m_net->connect("wss://echo.websocket.org");
}

int AppCoreWeb::init(int width, int height, bool linear_filter, int auto_close_secs) {
    PRINT_FUNCTION_NAME();
    
    do {
        if (AppCore::init(width, height, linear_filter, auto_close_secs) != 0) {
            break;
        }

        return 0;
    } while(false);
    return -1;
}

int AppCoreWeb::run() {
    PRINT_FUNCTION_NAME();

    const int fps = -1;
    const bool simulate_infinite_loop = true;
    emscripten_set_main_loop_arg(s_main_loop, this, fps, simulate_infinite_loop);
    return 0;
}

void AppCoreWeb::render_imgui() {
    AppCore::render_imgui();

    {
        ImGui::Begin("Another Window");
        ImGui::Text("Hello from another window!");
        ImGui::End();
    }
}

void AppCoreWeb::update_app_info() {
    AppCore::update_app_info();
}

void AppCoreWeb::reset_gamesave() {
    AppCore::reset_gamesave();
    
    utils::web::web_fetch_persist_file_delete(consts::text::GAMESAVE_FILE_NAME);
}

std::unique_ptr<AppCore> AppCore::create_web() {
    return std::make_unique<AppCoreWeb>();
}