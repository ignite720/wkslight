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
    virtual void * renderer_as_mut_ptr() override { return m_renderer; }
    virtual void update_app_info() override;

    virtual void play_audio_music(int index) const override;
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
    
    do {
        if (AppCore::init(width, height, linear_filter) != 0) {
            break;
        }
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
            printf("%s => Failed to initialize SDL: %s\n", FUNCTION_NAME, SDL_GetError());
            break;
        }

        if (linear_filter) {
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                break;
            }
        }
        
        Uint32 flags = SDL_WINDOW_SHOWN;
        m_window = SDL_CreateWindow("AppCoreWeb", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
        if (!m_window) {
            printf("%s => Failed to create Window: %s\n", FUNCTION_NAME, SDL_GetError());
            break;
        }

        flags = (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        m_renderer = SDL_CreateRenderer(m_window, -1, flags);
        if (!m_renderer) {
            printf("%s => Failed to create Renderer: %s\n", FUNCTION_NAME, SDL_GetError());
            break;
        }

        if (SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND) != 0) {
            break;
        }
        
        const int img_loaders = (IMG_INIT_JPG | IMG_INIT_PNG);
        if (IMG_Init(img_loaders) != img_loaders) {
            printf("%s => Failed to initialize SDL_image: %s\n", FUNCTION_NAME, IMG_GetError());
            break;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("%s => Failed to initialize SDL_mixer: %s\n", FUNCTION_NAME, Mix_GetError());
            break;
        }

        if (TTF_Init() != 0) {
            printf("%s => Failed to initialize SDL_ttf: %s\n", FUNCTION_NAME, TTF_GetError());
            break;
        }
    
        {
            m_resource_bundle = std::make_unique<ResourceBundle>(this);
            m_resource_bundle->put(ResourceBundle::AUDIO_MUSIC_INSERT_COIN, std::make_unique<AudioMusic>("assets/sounds/Insert Coin.ogg"));
            m_resource_bundle->put(ResourceBundle::AUDIO_MUSIC_ITEM_SHOP, std::make_unique<AudioMusic>("assets/sounds/Item Shop.ogg"));
            this->play_audio_music(ResourceBundle::AUDIO_MUSIC_ITEM_SHOP);

            m_resource_bundle->put(ResourceBundle::AUDIO_CLIP_BOUNCE, std::make_unique<AudioClip>("assets/sounds/bounce.wav"));
            m_resource_bundle->put(ResourceBundle::AUDIO_CLIP_COIN, std::make_unique<AudioClip>("assets/sounds/coin.wav"));
            m_resource_bundle->put(ResourceBundle::AUDIO_CLIP_HIT, std::make_unique<AudioClip>("assets/sounds/hit.wav"));
            m_resource_bundle->put(ResourceBundle::AUDIO_CLIP_LOSE, std::make_unique<AudioClip>("assets/sounds/lose.wav"));

            m_resource_bundle->put(ResourceBundle::FONT_PRESS_START_2P, std::make_unique<Font>("assets/fonts/PressStart2P/PressStart2P.ttf", 12));
        }

        m_ball = std::make_unique<Ball>(this);
        m_paddle = std::make_unique<Paddle>(this);

        utils::web::web_fetch("example.json");
        utils::web::web_fetch("https://httpbin.org/xml");

        auto &game_info_stats = this->app_info_as_mut().game_info.stats;
        auto _ret = utils::web::web_fetch_persist_file_load_sync(this, consts::text::GAME_SAVE_FILE_NAME, &game_info_stats, sizeof(game_info_stats), utils::web::WebFetchUserData::USAGE_GAME_INFO_STATS);
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

void AppCoreWeb::update() {
    SDL_Event evt = {0};
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            if (evt.button.button == SDL_BUTTON_LEFT) {
                printf("Click: (%d, %d)\n", evt.button.x, evt.button.y);

                this->restart();
            }
        }

        switch (evt.key.keysym.sym) {
            case SDLK_f: {
                if (evt.key.type == SDL_KEYDOWN) {
                    this->app_info_as_mut().game_info.paddle_friction = !this->app_info_as_mut().game_info.paddle_friction;
                }
            } break;
            case SDLK_i:
            case SDLK_SPACE: {
                if (evt.key.type == SDL_KEYDOWN) {
                    this->restart();
                }
            } break;
            case SDLK_u: {
                if (evt.key.type == SDL_KEYDOWN) {
                    utils::web::web_fetch_persist_file_delete(consts::text::GAME_SAVE_FILE_NAME);
                }
            } break;
            case SDLK_v: {
                if (evt.key.type == SDL_KEYDOWN) {
                    this->app_info_as_mut().config.logger_verbose = !this->app_info_as_mut().config.logger_verbose;
                }
            } break;
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_w, SDLK_UP, UP);
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_s, SDLK_DOWN, DOWN);
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_a, SDLK_LEFT, LEFT);
            CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_d, SDLK_RIGHT, RIGHT);
        }
    }

    this->update_app_info();
    {
        const auto dt = this->app_info_as_ref().stats.delta_time;

        m_ball->update(dt);
        m_ball->update_collision(dt, &m_paddle->rect_as_ref());
        
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
        const auto &app_info = this->app_info_as_ref();

        {
            auto text = ("fps: " + std::to_string(app_info.stats.fps)
                + "\ndelta time: " + std::to_string(app_info.stats.delta_time)
                + "\nlogger verbose(V): " + std::to_string(app_info.config.logger_verbose)
                + "\npaddle friction(F): " + std::to_string(app_info.game_info.paddle_friction)
                + "\nreset score(U): "
                + "\nhigh score: " + std::to_string(app_info.game_info.stats.high_score)
                + "\nrounds: " + std::to_string(app_info.game_info.stats.num_rounds)
                + "\nscore: " + std::to_string(app_info.game_info.stats.score)
            );
            m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, text, 1.0f, 5.0f, 5.0f);
        }

        {
            m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, "RIGHT TOP", 0.75f, app_info.window_width, 0.0f, consts::anchor_point::RIGHT_TOP, consts::colors::PURPLE);
            m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, "RIGHT BOTTOM", 0.5f, app_info.window_width, app_info.window_height, consts::anchor_point::RIGHT_BOTTOM, consts::colors::TEAL);
            m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, "LEFT BOTTOM", 0.5f, 0.0f, app_info.window_height, consts::anchor_point::LEFT_BOTTOM, consts::colors::GOLD);
        }

        if (m_ball->get_dead()) {
            m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, consts::text::GAME_OVER_HINT, 2.0f, app_info.window_width * 0.5f, app_info.window_height * 0.5f, consts::anchor_point::CENTER, consts::colors::ORANGE);
        }
    }

    SDL_RenderPresent(m_renderer);
}

void AppCoreWeb::restart() {
    if (!this->app_info_as_ref().game_info.game_over) {
        return;
    }

    AppCore::restart();

    auto &app_info = this->app_info_as_mut();
    app_info.game_info.stats.num_rounds++;
    app_info.game_info.stats.score = 0;

    m_ball->respawn();
}

void AppCoreWeb::update_app_info() {
    auto lam_update_app_info_stats = [](AppInfo::Stats &stats) {
        stats.now = utils::sdl::now();
        stats.delta_time = (stats.now - stats.last_time);
        stats.last_time = stats.now;

        stats.staging.frames_accumulated++;
        stats.staging.time_accumulated += stats.delta_time;
        if (stats.staging.time_accumulated >= 1.0f) {
            stats.staging.time_accumulated = 0.0f;

            stats.fps = stats.staging.frames_accumulated;
            stats.staging.frames_accumulated = 0;
        }
    };

    lam_update_app_info_stats(this->app_info_as_mut().stats);
}

void AppCoreWeb::play_audio_music(int index) const {
    m_resource_bundle->play_audio_music(static_cast<ResourceBundle::AUDIO_MUSIC>(index));
}

void AppCoreWeb::play_audio_clip(int index) const {
    m_resource_bundle->play_audio_clip(static_cast<ResourceBundle::AUDIO_CLIP>(index));
}

std::unique_ptr<AppCore> AppCore::create_web() {
    return std::make_unique<AppCoreWeb>();
}

#endif