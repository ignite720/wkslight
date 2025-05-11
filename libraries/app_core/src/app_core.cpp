#include "pch.h"

#include "app_core/app_core.h"

#if !TARGET_PLATFORM_ANDROID
#include "app_core/ball.h"
#include "app_core/font2.h"
#include "app_core/paddle.h"
#include "app_core/resource_bundle.h"

#include <clay/clay.h>
PRAGMA_WARNING_PUSH
PRAGMA_WARNING_IGNORE_CLANG("-Wnarrowing")
PRAGMA_WARNING_IGNORE_GCC("-Wnarrowing")
PRAGMA_WARNING_IGNORE_MSVC(4018 4244 4576 4838)
#include <clay/renderers/SDL2/clay_renderer_SDL2.c>
PRAGMA_WARNING_POP

#include <wkstk/simplerand.hpp>

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>

#define __CASE_PADDLE_MOVE_STATE_FROM_KEYS(key1_, key2_, state_) \
case key1_: \
case key2_: { \
    if (evt.key.type == SDL_KEYDOWN) { \
        m_paddle->set_move_state(m_paddle->get_move_state() | MOVE_STATE_##state_); \
    } else if (evt.key.type == SDL_KEYUP) { \
        m_paddle->set_move_state(m_paddle->get_move_state() ^ MOVE_STATE_##state_); \
    } \
} break

static void s_handle_clay_errors(Clay_ErrorData error_data) {
    printf("%s\n", error_data.errorText.chars);
}

static struct Clay {
    static constexpr auto COLOR_LIGHT = Clay_Color { 244, 235, 230, 255 };
    static constexpr auto COLOR_LIGHT_HOVER = Clay_Color { 224, 215, 210, 255 };

    static constexpr auto COLOR_RED = Clay_Color { 168, 66, 28, 255 };
    static constexpr auto COLOR_BLUE = Clay_Color { 0, 0, 255, 255 };
    static constexpr auto COLOR_ORANGE = Clay_Color { 225, 138, 50, 255 };

    static constexpr auto COLOR_TOP_BORDER_1 = Clay_Color { 168, 66, 28, 255 };
    static constexpr auto COLOR_TOP_BORDER_2 = Clay_Color { 223, 110, 44, 255 };
    static constexpr auto COLOR_TOP_BORDER_3 = Clay_Color { 225, 138, 50, 255 };
    static constexpr auto COLOR_TOP_BORDER_4 = Clay_Color { 236, 189, 80, 255 };
    static constexpr auto COLOR_TOP_BORDER_5 = Clay_Color { 240, 213, 137, 255 };

    static constexpr auto COLOR_BLOB_BORDER_1 = Clay_Color { 168, 66, 28, 255 };
    static constexpr auto COLOR_BLOB_BORDER_2 = Clay_Color { 203, 100, 44, 255 };
    static constexpr auto COLOR_BLOB_BORDER_3 = Clay_Color { 225, 138, 50, 255 };
    static constexpr auto COLOR_BLOB_BORDER_4 = Clay_Color { 236, 159, 70, 255 };
    static constexpr auto COLOR_BLOB_BORDER_5 = Clay_Color { 240, 189, 100, 255 };

    static void landing_page_blob(int index, uint16_t font_size, Clay_Color color, Clay_String text, Clay_String image_url);
    static void landing_page_desktop(const AppInfo &app_info);

    void init(const AppInfo &app_info, Font2 *font2);

    int debug_mode = 0;
    std::unique_ptr<char[]> mem;

    SDL2_Font fonts[ResourceBundle::FONT_COUNT] = {};
    Clay_TextElementConfig header_text_config = Clay_TextElementConfig { .textColor = {61, 26, 5, 255}, .fontId = ResourceBundle::FONT_PRESS_START_2P, .fontSize = 24 };
} s_clay;

void Clay::init(const AppInfo &app_info, Font2 *font2) {
    assert(!this->mem);

    this->fonts[ResourceBundle::FONT_PRESS_START_2P] = SDL2_Font {
        .fontId = ResourceBundle::FONT_PRESS_START_2P,
        .font = font2->ttf_font_as_mut_ptr(),
    };

    auto size = Clay_MinMemorySize();
    this->mem = std::make_unique<char[]>(size);

    Clay_Arena mem_arena = Clay_CreateArenaWithCapacityAndMemory(size, this->mem.get());
    Clay_Initialize(mem_arena, Clay_Dimensions { app_info.window_width, app_info.window_height }, Clay_ErrorHandler { s_handle_clay_errors });
    Clay_SetMeasureTextFunction(SDL2_MeasureText, s_clay.fonts);
}

void Clay::landing_page_blob(int index, uint16_t font_size, Clay_Color color, Clay_String text, Clay_String image_url) {
    CLAY({ .id = CLAY_IDI("HeroBlob", index), .layout = { .sizing = { CLAY_SIZING_GROW(.max = 480) }, .padding = CLAY_PADDING_ALL(16), .childGap = 16, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER} }, .cornerRadius = CLAY_CORNER_RADIUS(10), .border = { .color = color, .width = { 2, 2, 2, 2 } } }) {
        CLAY({ .id = CLAY_IDI("CheckImage", index), .layout = { .sizing = { CLAY_SIZING_FIXED(32) } }, .image = { .sourceDimensions = { 128, 128 } } }) {}
        CLAY_TEXT(text, CLAY_TEXT_CONFIG({ .textColor = color, .fontId = ResourceBundle::FONT_PRESS_START_2P, .fontSize = font_size }));
    }
}

void Clay::landing_page_desktop(const AppInfo &app_info) {
    CLAY({ .id = CLAY_ID("LandingPage1Desktop"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(.min = app_info.window_height - 70) }, .padding = { 50, 50 }, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER} } }) {
        CLAY({ .id = CLAY_ID("LandingPage1"), .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, .padding = CLAY_PADDING_ALL(32), .childGap = 32, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER} }, .border = { .color = Clay::COLOR_RED, .width = { .left = 2, .right = 2 } } }) {
            CLAY({ .id = CLAY_ID("LeftText"), .layout = { .sizing = { .width = CLAY_SIZING_PERCENT(0.55f) }, .childGap = 8, .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
                CLAY_TEXT(CLAY_STRING("Clay is a flex-box style UI auto layout library in C, with declarative syntax and microsecond performance."), CLAY_TEXT_CONFIG({ .textColor = Clay::COLOR_RED, .fontId = ResourceBundle::FONT_PRESS_START_2P, .fontSize = 56 }));
                CLAY({ .id = CLAY_ID("LandingPageSpacer"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(32) } } }) {}
                CLAY_TEXT(CLAY_STRING("Clay is laying out this webpage right now!"), CLAY_TEXT_CONFIG({ .textColor = Clay::COLOR_ORANGE, .fontId = ResourceBundle::FONT_PRESS_START_2P, .fontSize = 36 }));
            }
            CLAY({ .id = CLAY_ID("HeroImageOuter"), .layout = { .sizing = { .width = CLAY_SIZING_PERCENT(0.45f) }, .childGap = 16, .childAlignment = { CLAY_ALIGN_X_CENTER }, .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
                landing_page_blob(1, 32, Clay::COLOR_BLOB_BORDER_5, CLAY_STRING("High performance"), CLAY_STRING("/clay/images/check_5.png"));
                landing_page_blob(2, 32, Clay::COLOR_BLOB_BORDER_4, CLAY_STRING("Flexbox-style responsive layout"), CLAY_STRING("/clay/images/check_4.png"));
                landing_page_blob(3, 32, Clay::COLOR_BLOB_BORDER_3, CLAY_STRING("Declarative syntax"), CLAY_STRING("/clay/images/check_3.png"));
                landing_page_blob(4, 32, Clay::COLOR_BLOB_BORDER_2, CLAY_STRING("Single .h file for C/C++"), CLAY_STRING("/clay/images/check_2.png"));
                landing_page_blob(5, 32, Clay::COLOR_BLOB_BORDER_1, CLAY_STRING("Compile to 15kb .wasm"), CLAY_STRING("/clay/images/check_1.png"));
            }
        }
    }
}

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
        switch (evt.type) {
            case SDL_MOUSEBUTTONDOWN: {
                if (evt.button.button == SDL_BUTTON_LEFT) {
                    printf("Click: (%d, %d)\n", evt.button.x, evt.button.y);
    
                    this->restart();
                }
            } break;
            case SDL_MOUSEWHEEL: {
                m_input.mouse_wheel.x = float(evt.wheel.x), m_input.mouse_wheel.y = float(evt.wheel.y);
            } break;
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
    utils::sdl::clear_with_color(m_renderer, consts::colors::GRAY);

    this->render_background();
    this->render_foreground();

    if (true) {
        this->render_imgui_begin();
        this->render_imgui();
        this->render_imgui_end();
    }
    
    SDL_RenderPresent(m_renderer);
}

void AppCore::render_background() {
    {
        int w = 0, h = 0;
        SDL_GetWindowSize(m_window, &w, &h);

        m_app_info.window_width = float(w);
        m_app_info.window_height = float(h);
    }

    {
        Clay_SetLayoutDimensions(Clay_Dimensions { m_app_info.window_width, m_app_info.window_height });

        int mouse_x = 0, mouse_y = 0;
        auto mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
        m_input.mouse_position.x = float(mouse_x), m_input.mouse_position.y = float(mouse_y);
        m_input.is_mouse_down = (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT));

        Clay_SetPointerState(Clay_Vector2 { m_input.mouse_position.x, m_input.mouse_position.y }, m_input.is_mouse_down);
        Clay_UpdateScrollContainers(true, Clay_Vector2 { m_input.mouse_wheel.x, m_input.mouse_wheel.y }, m_app_info.stats.delta_time);
    }
    
    Clay_BeginLayout();
    CLAY({ .id = CLAY_ID("OuterContainer"), .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, .layoutDirection = CLAY_TOP_TO_BOTTOM }, .backgroundColor = Clay::COLOR_LIGHT }) {
        CLAY({ .id = CLAY_ID("Header"), .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(50) }, .padding = { 32, 32 }, .childGap = 16, .childAlignment = { CLAY_ALIGN_X_LEFT, CLAY_ALIGN_Y_CENTER } } }) {
            CLAY_TEXT(CLAY_STRING("Clay"), &s_clay.header_text_config);
            CLAY({ .id = CLAY_ID("Spacer"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(0) } } }) {}
            CLAY({ .id = CLAY_ID("LinkDocsOuter"), .layout = { .padding = {8, 8} }, .userData = nullptr }) {
                CLAY_TEXT(CLAY_STRING("Docs"), CLAY_TEXT_CONFIG({ .textColor = {61, 26, 5, 255}, .fontId = 0, .fontSize = 24 }));
            }
            CLAY({ .id = CLAY_ID("DebugMode"), .layout = { .padding = {16, 16, 6, 6} },
                .backgroundColor = Clay_Hovered() ? Clay::COLOR_LIGHT_HOVER : Clay::COLOR_LIGHT,
                .cornerRadius = CLAY_CORNER_RADIUS(10),
                .border = { .color = Clay::COLOR_RED, .width = { 2, 2, 2, 2 } },
                .userData = nullptr,
            }) {
                CLAY_TEXT(CLAY_STRING("Debug"), CLAY_TEXT_CONFIG({ .textColor = { 61, 26, 5, 255 }, .fontId = ResourceBundle::FONT_PRESS_START_2P, .fontSize = 24 }));
            }
        }

        Clay_LayoutConfig top_border_config = Clay_LayoutConfig { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(4) } };
        CLAY({ .id = CLAY_ID("TopBorder1"), .layout = top_border_config, .backgroundColor = Clay::COLOR_TOP_BORDER_5 }) {}
        CLAY({ .id = CLAY_ID("TopBorder2"), .layout = top_border_config, .backgroundColor = Clay::COLOR_TOP_BORDER_4 }) {}
        CLAY({ .id = CLAY_ID("TopBorder3"), .layout = top_border_config, .backgroundColor = Clay::COLOR_TOP_BORDER_3 }) {}
        CLAY({ .id = CLAY_ID("TopBorder4"), .layout = top_border_config, .backgroundColor = Clay::COLOR_TOP_BORDER_2 }) {}
        CLAY({ .id = CLAY_ID("TopBorder5"), .layout = top_border_config, .backgroundColor = Clay::COLOR_TOP_BORDER_1 }) {}
        CLAY({ .id = CLAY_ID("OuterScrollContainer"),
            .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, .layoutDirection = CLAY_TOP_TO_BOTTOM },
            .scroll = { .vertical = true },
            .border = { .color = Clay::COLOR_RED, .width = { .betweenChildren = 2 } }
        }) {
            Clay::landing_page_desktop(m_app_info);
        }
    }

    if (m_input.is_mouse_down && Clay_PointerOver(Clay_GetElementId(CLAY_STRING("DebugMode")))) {
        s_clay.debug_mode = ((s_clay.debug_mode + 1) % 3);
        
        Clay_SetDebugModeEnabled(s_clay.debug_mode);
    }

    Clay_RenderCommandArray render_cmds = Clay_EndLayout();
    Clay_SDL2_Render(m_renderer, render_cmds, s_clay.fonts);
}

void AppCore::render_foreground() {
    const auto lam_draw_text = [=](const std::string &text, float &y, float line_spacing = 3.0f) {
        int w = 0, h = 0;
        #if 0
        auto ret = m_resource_bundle->text_size(ResourceBundle::FONT_PRESS_START_2P, text, &w, &h);
        #else
        const auto rect = m_resource_bundle->draw_text(ResourceBundle::FONT_PRESS_START_2P, text, 1.0f, 5.0f, y);
        #endif
        h = int(rect.h);

        y += (h + line_spacing);
    };
    
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
        m_deletion_queue.push([=]() {
            SDL_Quit();
        });

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
        m_deletion_queue.push([=]() {
            SDL_DestroyWindow(m_window);
        });

        flags = (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        m_renderer = SDL_CreateRenderer(m_window, -1, flags);
        if (!m_renderer) {
            printf("%s => Failed to create Renderer: %s\n", FUNCTION_NAME, SDL_GetError());
            break;
        }
        m_deletion_queue.push([=]() {
            SDL_DestroyRenderer(m_renderer);
        });

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
        m_deletion_queue.push([=]() {
            IMG_Quit();
        });

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("%s => Failed to initialize SDL_mixer: %s\n", FUNCTION_NAME, Mix_GetError());
            break;
        }
        m_deletion_queue.push([=]() {
            Mix_CloseAudio();
        });

        if (TTF_Init() != 0) {
            printf("%s => Failed to initialize SDL_ttf: %s\n", FUNCTION_NAME, TTF_GetError());
            break;
        }
        m_deletion_queue.push([=]() {
            TTF_Quit();
        });
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
    m_deletion_queue.push([=]() {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    });
    return true;
}

bool AppCore::init_assets() {
    Font2 *font2 = nullptr;

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

        font2 = m_resource_bundle->put<Font2>(ResourceBundle::FONT_PRESS_START_2P, "assets/fonts/PressStart2P/PressStart2P.ttf", 12);
    }

    {
        m_ball = new Ball(*this);
        m_paddle = new Paddle(*this);
        m_deletion_queue.push([=]() {
            SAFE_DELETE(m_paddle);
            SAFE_DELETE(m_ball);
            SAFE_DELETE(m_resource_bundle);
        });
    }
    
    assert(font2);
    s_clay.init(m_app_info, font2);
    return true;
}

void AppCore::drop() {
    m_deletion_queue.flush();
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