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

    virtual int init(int width, int height, bool linear_filter) override;
    virtual int run() override;

    virtual void update() override;
    virtual void render() override;

    virtual void restart() override;
    virtual void * renderer_as_void_p() override { return m_renderer; }
    virtual void play_audio_clip(int index) const override;

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    std::unique_ptr<ResourceBundle> m_resource_bundle;
    std::unique_ptr<Ball> m_ball;
    std::unique_ptr<Paddle> m_paddle;
};

AppCoreWeb::~AppCoreWeb() {
    m_paddle.reset();
    m_ball.reset();
    m_resource_bundle.reset();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}

int AppCoreWeb::init(int width, int height, bool linear_filter) {
    PRINT_FUNCTION_NAME();
    
    AppCore::init(width, height, linear_filter);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("%s => Failed to initialize SDL: %s\n", FUNCTION_NAME, SDL_GetError());
        return -1;
    }

    if (linear_filter) {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            return -2;
        }
    }
    
    Uint32 flags = SDL_WINDOW_SHOWN;
    m_window = SDL_CreateWindow("AppCoreWeb", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if (!m_window) {
        printf("%s => Failed to create Window: %s\n", FUNCTION_NAME, SDL_GetError());
        return -3;
    }

    flags = (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    m_renderer = SDL_CreateRenderer(m_window, -1, flags);
    if (!m_renderer) {
        printf("%s => Failed to create Renderer: %s\n", FUNCTION_NAME, SDL_GetError());
        return -4;
    }

    if (SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND) != 0) {
        return -5;
    }
    
    const int img_loaders = (IMG_INIT_JPG | IMG_INIT_PNG);
    if (IMG_Init(img_loaders) != img_loaders) {
        printf("%s => Failed to initialize SDL_image: %s\n", FUNCTION_NAME, IMG_GetError());
        return -6;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("%s => Failed to initialize SDL_mixer: %s\n", FUNCTION_NAME, Mix_GetError());
        return -7;
    }

    if (TTF_Init() != 0) {
        printf("%s => Failed to initialize SDL_ttf: %s\n", FUNCTION_NAME, TTF_GetError());
        return -8;
    }
    
    {
        m_resource_bundle = std::make_unique<ResourceBundle>();
        m_resource_bundle->bgm = std::make_unique<AudioMusic>("assets/sounds/Item Shop.ogg");
        m_resource_bundle->play_bgm();

        m_resource_bundle->clips[ResourceBundle::AUDIO_CLIP_BOUNCE] = std::make_unique<AudioClip>("assets/sounds/bounce.wav");
        m_resource_bundle->clips[ResourceBundle::AUDIO_CLIP_CLICK] = std::make_unique<AudioClip>("assets/sounds/click.wav");
        m_resource_bundle->clips[ResourceBundle::AUDIO_CLIP_HIT] = std::make_unique<AudioClip>("assets/sounds/hit.wav");

        m_resource_bundle->fonts[ResourceBundle::FONT_PRESS_START_2P] = std::make_unique<Font>("assets/fonts/PressStart2P/PressStart2P.ttf", 12);

        m_resource_bundle->textures[ResourceBundle::TEXTURE_1] = std::make_unique<Texture>(this);
    }

    m_ball = std::make_unique<Ball>(this);
    m_paddle = std::make_unique<Paddle>(this);

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
    {
        m_app_info.stats.now = utils::sdl::now();
        m_app_info.stats.delta_time = (m_app_info.stats.now - m_app_info.stats.last_time);
        m_app_info.stats.last_time = m_app_info.stats.now;

        m_app_info.stats.staging.frames_accumulated++;
        m_app_info.stats.staging.time_accumulated += m_app_info.stats.delta_time;
        if (m_app_info.stats.staging.time_accumulated >= 1.0f) {
            m_app_info.stats.staging.time_accumulated = 0.0f;
            
            m_app_info.stats.fps = m_app_info.stats.staging.frames_accumulated;
            m_app_info.stats.staging.frames_accumulated = 0;
        }
    }

    SDL_Event evt = {0};
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            m_resource_bundle->play_audio_clip(ResourceBundle::AUDIO_CLIP_CLICK);
            
            if (evt.button.button == SDL_BUTTON_LEFT) {
                printf("Click: (%d, %d)\n", evt.button.x, evt.button.y);
            }
        }

        switch (evt.key.keysym.sym) {
            case SDLK_f: {
                if (evt.key.type == SDL_KEYDOWN) {
                    m_app_info.game_info.paddle_friction = !m_app_info.game_info.paddle_friction;
                }
            } break;
            case SDLK_v: {
                if (evt.key.type == SDL_KEYDOWN) {
                    m_app_info.config.logger_verbose = !m_app_info.config.logger_verbose;
                }
            } break;
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_w, SDLK_UP, UP);
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_s, SDLK_DOWN, DOWN);
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_a, SDLK_LEFT, LEFT);
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_d, SDLK_RIGHT, RIGHT);
        }
    }

    {
        const auto dt = m_app_info.stats.delta_time;

        m_ball->update(dt);
        if (m_ball->update_collision(m_paddle->get_rect())) {
            m_app_info.game_info.stats.num_streaks++;
        }

        m_paddle->update(dt);
    }
}

void AppCoreWeb::render() {
    utils::sdl::clear_with_color(m_renderer, consts::colors::GRAY);

    {
        m_ball->render();
        m_paddle->render();
    }
    
    {
        auto text = ("fps: " + std::to_string(m_app_info.stats.fps)
            + "delta time: " + std::to_string(m_app_info.stats.delta_time)
            + "\nlogger verbose(press V to toggle): " + std::to_string(m_app_info.config.logger_verbose)
            + "\npaddle friction(press F to toggle): " + std::to_string(m_app_info.game_info.paddle_friction)
            + "\nstreaks: " + std::to_string(m_app_info.game_info.stats.num_streaks));
        auto _ret = m_resource_bundle->textures[ResourceBundle::TEXTURE_1]->load_from_text(m_resource_bundle->fonts[ResourceBundle::FONT_PRESS_START_2P]->get_raw_handle(), text.c_str(), consts::colors::WHITE);
        m_resource_bundle->textures[ResourceBundle::TEXTURE_1]->set_blend_mode(SDL_BLENDMODE_BLEND);

        const auto w = static_cast<float>(m_resource_bundle->textures[ResourceBundle::TEXTURE_1]->get_width());
        const auto h = static_cast<float>(m_resource_bundle->textures[ResourceBundle::TEXTURE_1]->get_height());
        const float scale = 0.5f;
        const auto dst_rect = SDL_FRect { 5.0f, 5.0f, w * scale, h * scale };
        m_resource_bundle->textures[ResourceBundle::TEXTURE_1]->render(&dst_rect);
    }

    SDL_RenderPresent(m_renderer);
}

void AppCoreWeb::restart() {
    m_app_info.game_info.stats.num_streaks = 0;
}

void AppCoreWeb::play_audio_clip(int index) const {
    m_resource_bundle->play_audio_clip(static_cast<ResourceBundle::AUDIO_CLIP>(index));
}

std::unique_ptr<AppCore> AppCore::create_web() {
    return std::make_unique<AppCoreWeb>();
}

#endif