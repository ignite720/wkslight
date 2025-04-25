#include "app_core/app_core.h"

#if !TARGET_PLATFORM_ANDROID
#include "app_core/ball.h"
#include "app_core/font.h"
#include "app_core/paddle.h"
#include "app_core/resource_bundle.h"

#include <foo/foo_macros.h>

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>

#include <simplerand/simplerand.hpp>

#define __CASE_PADDLE_MOVE_STATE_FROM_KEYS(key1_, key2_, state_) \
case key1_: \
case key2_: { \
    if (evt.key.type == SDL_KEYDOWN) { \
        m_paddle->set_move_state(m_paddle->get_move_state() | MOVE_STATE_##state_); \
    } else if (evt.key.type == SDL_KEYUP) { \
        m_paddle->set_move_state(m_paddle->get_move_state() ^ MOVE_STATE_##state_); \
    } \
} break

std::unique_ptr<AppCore> AppCore::create() {
    #if TARGET_PLATFORM_ANDROID
    return AppCore::create_android();
    #elif TARGET_PLATFORM_PC
    return AppCore::create_pc();
    #elif TARGET_PLATFORM_UWP
    return AppCore::create_uwp();
    #elif TARGET_PLATFORM_WEB
    return AppCore::create_web();
    #else
    return nullptr;
    #endif
}

AppCore::~AppCore() {
    PRINT_FUNCTION_NAME();

    this->drop();
}

int AppCore::init(int width, int height, bool linear_filter, int auto_close_secs) {
    PRINT_FUNCTION_NAME();

    m_app_info.window_width = float(width);
    m_app_info.window_height = float(height);
    m_app_info.linear_filter = linear_filter;
    m_app_info.auto_close_timer = float(auto_close_secs);

    simplerand::from_seed(static_cast<unsigned>(std::time(nullptr)));

    do {
        if (!this->init_sdl2()) {
            break;
        }

        if (!this->init_sdl2_libs()) {
            break;
        }

        if (!this->init_imgui()) {
            break;
        }

        if (!this->init_assets()) {
            break;
        }

        return 0;
    } while(false);
    return -1;
}

int AppCore::run() {
    while (!m_app_info.quit) {
        this->update();
        this->render();
    }
    return 0;
}

void AppCore::update() {
    SDL_Event evt = {};
    while (SDL_PollEvent(&evt)) {
        ImGui_ImplSDL2_ProcessEvent(&evt);

        if (evt.type == SDL_QUIT) {
            m_app_info.quit = true;
            break;
        }

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
            case SDLK_v: {
                if (evt.key.type == SDL_KEYDOWN) {
                    this->app_info_as_mut().config.logger_verbose = !this->app_info_as_mut().config.logger_verbose;
                }
            } break;
            case SDLK_x: {
                if (evt.key.type == SDL_KEYDOWN) {
                    this->reset_gamesave();
                }
            } break;
            __CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_w, SDLK_UP, UP);
            __CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_s, SDLK_DOWN, DOWN);
            __CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_a, SDLK_LEFT, LEFT);
            __CASE_PADDLE_MOVE_STATE_FROM_KEYS(SDLK_d, SDLK_RIGHT, RIGHT);
        }
    }

    #if !TARGET_PLATFORM_WEB
    if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED) {
        SDL_Delay(10);
    }
    #endif

    this->update_app_info();
    {
        const auto dt = this->app_info_as_ref().stats.delta_time;

        m_ball->update(dt);
        m_ball->update_collision(dt, &m_paddle->rect_as_ref());
        
        m_paddle->update(dt);
    }
}

void AppCore::render() {
    {
        const auto lam_draw_text = [=](const String &text, float &y, float line_spacing = 3.0f) {
            int w = 0, h = 0;
            //auto ret = m_resource_bundle->text_size(ResourceBundle::FONT_PRESS_START_2P, text, &w, &h);
            const auto rect = m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, text, 1.0f, 5.0f, y);
            h = int(rect.h);
    
            y += (h + line_spacing);
        };
    
        utils::sdl::clear_with_color(m_renderer, consts::colors::GRAY);
    
        {
            m_ball->render();
            m_paddle->render();
        }
        
        {
            const auto &app_info = this->app_info_as_ref();
    
            {
                float y = 25.0f;
    
                {
                    auto text = ("fps: " + std::to_string(app_info.stats.fps));
                    lam_draw_text(text, y);
                }
    
                {
                    auto text = utils::string::format("delta time: %.3f", app_info.stats.delta_time);
                    lam_draw_text(text, y);
                }
    
                {
                    auto text = (
                        "logger verbose(V): " + std::to_string(app_info.config.logger_verbose) + "\n" +
                        "paddle friction(F): " + std::to_string(app_info.game_info.paddle_friction) + "\n" +
                        "reset gamesave(X): "
                    );
                    lam_draw_text(text, y);
                }
    
                {
                    auto text = (
                        "high score: " + std::to_string(app_info.gamesave.high_score) + "\n" +
                        "rounds: " + std::to_string(app_info.game_info.stats.num_rounds) + "\n" +
                        "score: " + std::to_string(app_info.game_info.stats.score)
                    );
                    lam_draw_text(text, y);
                }
            }
    
            {
                m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, "LEFT TOP", 0.75f, 0.0f, 0.0f, consts::anchor_point::LEFT_TOP, consts::colors::YELLOW);
                m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, "RIGHT TOP", 0.75f, app_info.window_width, 0.0f, consts::anchor_point::RIGHT_TOP, consts::colors::PURPLE);
                m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, "RIGHT BOTTOM", 0.5f, app_info.window_width, app_info.window_height, consts::anchor_point::RIGHT_BOTTOM, consts::colors::TEAL);
                m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, "LEFT BOTTOM", 0.5f, 0.0f, app_info.window_height, consts::anchor_point::LEFT_BOTTOM, consts::colors::PINK);
            }
    
            if (m_ball->get_dead()) {
                m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, consts::text::GAME_OVER_HINT, 2.0f, app_info.window_width * 0.5f, app_info.window_height * 0.5f, consts::anchor_point::CENTER, consts::colors::ORANGE);
            }
        }
    }

    if (true) {
        this->render_imgui_begin();
        this->render_imgui();
        this->render_imgui_end();
    }
    
    SDL_RenderPresent(m_renderer);
}

void AppCore::render_imgui() {
    if (m_app_info.show_demo_window) {
        ImGui::ShowDemoWindow(&m_app_info.show_demo_window);
    }

    {
        ImGui::Begin("Hello, world!");
        ImGui::Checkbox("Demo Window", &m_app_info.show_demo_window);

        {
            SDL_version compiled, linked;

            SDL_VERSION(&compiled);
            SDL_GetVersion(&linked);
            ImGui::Text("SDL: %d.%d.%d(C %u.%u.%u, L %u.%u.%u)",
                SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL,
                compiled.major, compiled.minor, compiled.patch,
                linked.major, linked.minor, linked.patch
            );
            ImGui::Text("ImGui: %s", IMGUI_VERSION);
        }

        ImGui::Text("fps: %d", m_app_info.stats.fps);
        ImGui::End();
    }
}

void AppCore::restart() {
    if (!(this->app_info_as_ref().game_info.game_over
        //&& this->app_info_as_ref().game_info.stats_ready
    )) {
        return;
    }

    m_app_info.game_info.game_over = false;

    auto &app_info = this->app_info_as_mut();
    app_info.game_info.stats.num_rounds++;
    app_info.game_info.stats.score = 0;

    m_ball->respawn();
}

void AppCore::reset_gamesave() {
    m_app_info.gamesave = {};
}

void AppCore::update_app_info() {
    const auto lam_update_app_info_stats = [](AppInfo::Stats &stats) {
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

    if (m_app_info.auto_close_timer > 0.0f) {
        m_app_info.auto_close_timer -= m_app_info.stats.delta_time;
        if (m_app_info.auto_close_timer <= 0.0f) {
            m_app_info.quit = true;
        }
    }

    lam_update_app_info_stats(this->app_info_as_mut().stats);
}

void AppCore::play_audio_music(int index) const {
    m_resource_bundle->play_audio_music(static_cast<ResourceBundle::AUDIO_MUSIC>(index));
}

void AppCore::play_audio_clip(int index) const {
    m_resource_bundle->play_audio_clip(static_cast<ResourceBundle::AUDIO_CLIP>(index));
}

bool AppCore::init_sdl2() {
    do {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
            printf("%s => Failed to initialize SDL: %s\n", FUNCTION_NAME, SDL_GetError());
            break;
        }

        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
        if (m_app_info.linear_filter) {
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                break;
            }
        }
        
        Uint32 flags = (SDL_WINDOW_SHOWN/* | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI*/);
        m_window = SDL_CreateWindow("App",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            int(m_app_info.window_width), int(m_app_info.window_height),
            flags
        );
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

        return true;
    } while(false);
    return false;
}

bool AppCore::init_sdl2_libs() {
    do {
        const int img_loaders = (IMG_INIT_JPG | IMG_INIT_PNG);
        if ((IMG_Init(img_loaders) & img_loaders) != img_loaders) {
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

        return true;
    } while(false);
    return false;
}

bool AppCore::init_imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    
    ImGui::StyleColorsClassic();
    
    ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer2_Init(m_renderer);
    return true;
}

bool AppCore::init_assets() {
    {
        m_resource_bundle = new ResourceBundle(*this);
        m_resource_bundle->put<AudioMusic>(ResourceBundle::AUDIO_MUSIC_INSERT_COIN, "assets/sounds/Insert Coin.ogg");
        m_resource_bundle->put<AudioMusic>(ResourceBundle::AUDIO_MUSIC_ITEM_SHOP, "assets/sounds/Item Shop.ogg");
        this->play_audio_music(ResourceBundle::AUDIO_MUSIC_ITEM_SHOP);

        m_resource_bundle->put<AudioClip>(ResourceBundle::AUDIO_CLIP_BOUNCE, "assets/sounds/bounce.wav");
        m_resource_bundle->put<AudioClip>(ResourceBundle::AUDIO_CLIP_COIN, "assets/sounds/coin.wav");
        m_resource_bundle->put<AudioClip>(ResourceBundle::AUDIO_CLIP_HIT, "assets/sounds/hit.wav");
        m_resource_bundle->put<AudioClip>(ResourceBundle::AUDIO_CLIP_LOSE, "assets/sounds/lose.wav");
        m_resource_bundle->put<AudioClip>(ResourceBundle::AUDIO_CLIP_NEW_RECORD, "assets/sounds/new record.wav");

        m_resource_bundle->put<Font>(ResourceBundle::FONT_PRESS_START_2P, "assets/fonts/PressStart2P/PressStart2P.ttf", 12);
    }

    m_ball = new Ball(*this);
    m_paddle = new Paddle(*this);
    return true;
}

void AppCore::drop() {
    this->drop_assets();
    this->drop_imgui();
    this->drop_sdl2_libs();
    this->drop_sdl2();
}

void AppCore::drop_sdl2() {
    PRINT_FUNCTION_NAME();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void AppCore::drop_sdl2_libs() {
    PRINT_FUNCTION_NAME();

    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
}

void AppCore::drop_imgui() {
    PRINT_FUNCTION_NAME();

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void AppCore::drop_assets() {
    PRINT_FUNCTION_NAME();

    SAFE_DELETE(m_paddle);
    SAFE_DELETE(m_ball);
    SAFE_DELETE(m_resource_bundle);
}

void AppCore::render_imgui_begin() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void AppCore::render_imgui_end() {
    ImGuiIO &io = ImGui::GetIO();

    ImGui::Render();
    SDL_RenderSetScale(m_renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer);
}
#endif