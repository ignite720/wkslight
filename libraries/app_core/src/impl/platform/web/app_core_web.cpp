#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

#define CASE_PADDLE_MOVE_STATE_FROM_KEYS(key1_, key2_, state_) \
case key1_: \
case key2_: { \
    if (evt.key.type == SDL_KEYDOWN) { \
        m_paddle->set_move_state(m_paddle->get_move_state() | MOVE_STATE_##state_); \
    } else if (evt.key.type == SDL_KEYUP) { \
        m_paddle->set_move_state(m_paddle->get_move_state() ^ MOVE_STATE_##state_); \
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

    virtual void play_audio_clip(int index) override;

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    std::unique_ptr<AudioBundle> m_audio_bundle;
    std::unique_ptr<Ball> m_ball;
    std::unique_ptr<Paddle> m_paddle;
};

AppCoreWeb::~AppCoreWeb() {
    m_paddle.reset();
    m_audio_bundle.reset();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

int AppCoreWeb::init(int width, int height) {
    PRINT_FUNCTION_NAME();
    
    AppCore::init(width, height);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return -1;
    }

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
    
    m_audio_bundle = std::make_unique<AudioBundle>();
    m_audio_bundle->bgm = std::make_unique<AudioMusic>("assets/Item Shop.ogg");
    m_audio_bundle->play_bgm();

    m_audio_bundle->clips[AudioBundle::AUDIO_CLIP_BOUNCE] = std::make_unique<AudioClip>("assets/bounce.wav");
    m_audio_bundle->clips[AudioBundle::AUDIO_CLIP_CLICK] = std::make_unique<AudioClip>("assets/click.wav");
    m_audio_bundle->clips[AudioBundle::AUDIO_CLIP_HIT] = std::make_unique<AudioClip>("assets/hit.wav");

    m_ball = std::make_unique<Ball>(m_renderer, this);
    m_paddle = std::make_unique<Paddle>(m_renderer, 0.0f, m_window_height - Paddle::HEIGHT);

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
            m_audio_bundle->play_audio_clip(AudioBundle::AUDIO_CLIP_CLICK);
            
            if (evt.button.button == SDL_BUTTON_LEFT) {
                printf("Click: (%d, %d)\n", evt.button.x, evt.button.y);
            }
        }

        switch (evt.key.keysym.sym) {
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_w, SDLK_UP, UP);
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_s, SDLK_DOWN, DOWN);
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_a, SDLK_LEFT, LEFT);
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_d, SDLK_RIGHT, RIGHT);
        }
    }

    {
        m_ball->update(this);
        m_ball->update_collision(this, m_paddle->get_rect());

        m_paddle->update(this);
    }
}

void AppCoreWeb::render() {
    SDL_RenderClear(m_renderer);

    {
        const auto dst_rect = SDL_FRect { 0, 0, float(m_window_width), float(m_window_height) };
        utils::fill_rect_with_color(m_renderer, &dst_rect, SDL_Color { 95, 95, 95, 255 });
    }

    {
        m_ball->render();
        m_paddle->render();
    }

    SDL_RenderPresent(m_renderer);
}

void AppCoreWeb::play_audio_clip(int index) {
    m_audio_bundle->play_audio_clip(index);
}

std::unique_ptr<AppCore> AppCore::create_web() {
    return std::make_unique<AppCoreWeb>();
}

#endif