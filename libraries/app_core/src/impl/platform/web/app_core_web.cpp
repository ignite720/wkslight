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

int AppCoreWeb::init(int width, int height) {
    PRINT_FUNCTION_NAME();
    
    AppCore::init(width, height);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("%s => Failed to initialize SDL: %s\n", FUNCTION_NAME, SDL_GetError());
        return -1;
    }

    const Uint32 flags = SDL_RENDERER_PRESENTVSYNC;
    m_window = SDL_CreateWindow("AppCoreWeb", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if (!m_window) {
        printf("%s => Failed to create Window: %s\n", FUNCTION_NAME, SDL_GetError());
        return -1;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, flags);
    if (!m_renderer) {
        printf("%s => Failed to create Renderer: %s\n", FUNCTION_NAME, SDL_GetError());
        return -1;
    }

    if (SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND) != 0) {
        return -1;
    }
    
    const int img_loaders = (IMG_INIT_JPG | IMG_INIT_PNG);
    if (IMG_Init(img_loaders) != img_loaders) {
        printf("%s => Failed to initialize SDL_image: %s\n", FUNCTION_NAME, IMG_GetError());
        return -2;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("%s => Failed to initialize SDL_mixer: %s\n", FUNCTION_NAME, Mix_GetError());
        return -3;
    }

    if (TTF_Init() != 0) {
        printf("%s => Failed to initialize SDL_ttf: %s\n", FUNCTION_NAME, TTF_GetError());
        return -4;
    }
    
    {
        m_resource_bundle = std::make_unique<ResourceBundle>();
        m_resource_bundle->bgm = std::make_unique<AudioMusic>("assets/sounds/Item Shop.ogg");
        m_resource_bundle->play_bgm();

        m_resource_bundle->clips[ResourceBundle::AUDIO_CLIP_BOUNCE] = std::make_unique<AudioClip>("assets/sounds/bounce.wav");
        m_resource_bundle->clips[ResourceBundle::AUDIO_CLIP_CLICK] = std::make_unique<AudioClip>("assets/sounds/click.wav");
        m_resource_bundle->clips[ResourceBundle::AUDIO_CLIP_HIT] = std::make_unique<AudioClip>("assets/sounds/hit.wav");

        m_resource_bundle->fonts[ResourceBundle::FONT_PRESS_START_2P] = std::make_unique<Font>("assets/fonts/PressStart2P.ttf", 24);

        m_resource_bundle->textures[ResourceBundle::TEXTURE_1] = std::make_unique<Texture>(m_renderer);
        auto _ret = m_resource_bundle->textures[ResourceBundle::TEXTURE_1]->load_from_text(m_resource_bundle->fonts[ResourceBundle::FONT_PRESS_START_2P]->get_raw_handle(), "hello text", SDL_Color { 255, 255, 255 });
        m_resource_bundle->textures[ResourceBundle::TEXTURE_1]->set_blend_mode(SDL_BLENDMODE_BLEND);
    }

    m_ball = std::make_unique<Ball>(m_renderer, this);
    m_paddle = std::make_unique<Paddle>(m_renderer, this);

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
            m_resource_bundle->play_audio_clip(ResourceBundle::AUDIO_CLIP_CLICK);
            
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
    utils::sdl::clear_with_color(SDL_Color { 95, 95, 95, 255 });

    {
        m_ball->render();
        m_paddle->render();
    }
    
    {
        const auto dst_rect = SDL_FRect { 0.0f, 0.0f, m_window_width * 0.3f, 10.0f };
        m_resource_bundle->textures[ResourceBundle::TEXTURE_1]->render(&dst_rect);
    }

    SDL_RenderPresent(m_renderer);
}

void AppCoreWeb::play_audio_clip(int index) const {
    m_resource_bundle->play_audio_clip(static_cast<ResourceBundle::AUDIO_CLIP>(index));
}

std::unique_ptr<AppCore> AppCore::create_web() {
    return std::make_unique<AppCoreWeb>();
}

#endif