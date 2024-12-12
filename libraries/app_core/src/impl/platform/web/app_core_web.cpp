#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

#define CASE_PLAYER_MOVE_STATE_FROM_KEYS(key1_, key2_, state_) \
case key1_: \
case key2_: { \
    if (evt.key.type == SDL_KEYDOWN) { \
        m_player->set_move_state(m_player->get_move_state() | MOVE_STATE_##state_); \
    } else if (evt.key.type == SDL_KEYUP) { \
        m_player->set_move_state(m_player->get_move_state() ^ MOVE_STATE_##state_); \
    } \
} break

static void s_main_loop(void *arg) {
    auto *app_core = reinterpret_cast<AppCore *>(arg);

    app_core->update();
    app_core->render();
}

struct AppCoreWeb final : public AppCore {
    ~AppCoreWeb();

    virtual int init(int width, int height) override;
    virtual int run() override;

    virtual void update() override;
    virtual void render() override;

private:
    int m_window_width = 0;
    int m_window_height = 0;
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    std::unique_ptr<AudioBGM> m_bgm;
    std::unique_ptr<AudioClip> m_click_clip;
    std::unique_ptr<Player> m_player;
};

AppCoreWeb::~AppCoreWeb() {
    m_player.reset();
    m_click_clip.reset();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

int AppCoreWeb::init(int width, int height) {
    PRINT_FUNCTION_NAME();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return -1;
    }

    m_window_width = width;
    m_window_height = height;

    const Uint32 flags = SDL_RENDERER_PRESENTVSYNC;
    m_window = SDL_CreateWindow("AppCoreWeb", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    m_renderer = SDL_CreateRenderer(m_window, -1, flags);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("%s => Failed to initialize audio: %s\n", FUNCTION_NAME, Mix_GetError());
        return -2;
    }

    const int img_loaders = (IMG_INIT_JPG | IMG_INIT_PNG);
    if (IMG_Init(img_loaders) != img_loaders) {
        printf("%s => Failed to initialize required image format support: %s\n", FUNCTION_NAME, IMG_GetError());
        return -3;
    }
    
    m_bgm = std::make_unique<AudioBGM>();
    m_click_clip = std::make_unique<AudioClip>();
    m_click_clip->load_from_file("assets/click.wav");

    m_player = std::make_unique<Player>(m_renderer);

    utils::web_fetch("example.json");
    utils::web_fetch("https://httpbin.org/xml");
    return 0;
}

int AppCoreWeb::run() {
    PRINT_FUNCTION_NAME();

    const int fps = -1;
    const bool simulate_infinite_loop = true;
    emscripten_set_main_loop_arg(s_main_loop, this, fps, simulate_infinite_loop);
    return 0;
}

void AppCoreWeb::update() {
    SDL_Event evt = {0};
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            m_click_clip->play();
            
            if (evt.button.button == SDL_BUTTON_LEFT) {
                printf("Click: (%d, %d)\n", evt.button.x, evt.button.y);
            }
        }

        switch (evt.key.keysym.sym) {
            CASE_PLAYER_MOVE_STATE_FROM_KEYS(SDLK_w, SDLK_UP, UP);
            CASE_PLAYER_MOVE_STATE_FROM_KEYS(SDLK_s, SDLK_DOWN, DOWN);
            CASE_PLAYER_MOVE_STATE_FROM_KEYS(SDLK_a, SDLK_LEFT, LEFT);
            CASE_PLAYER_MOVE_STATE_FROM_KEYS(SDLK_d, SDLK_RIGHT, RIGHT);
        }
    }

    m_player->update();
}

void AppCoreWeb::render() {
    SDL_RenderClear(m_renderer);

    {
        const auto dst_rect = SDL_Rect { 0, 0, m_window_width, m_window_height };
        utils::fill_rect_with_color(m_renderer, &dst_rect, 95, 95, 95, 255);
    }

    m_player->render(m_renderer);
    SDL_RenderPresent(m_renderer);
}

std::unique_ptr<AppCore> AppCore::create_web() {
    return std::make_unique<AppCoreWeb>();
}

#endif