#include "app_core/app_core.h"

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>

AppCore::~AppCore() {
    PRINT_FUNCTION_NAME();

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

int AppCore::init(int width, int height, bool linear_filter) {
    PRINT_FUNCTION_NAME();

    m_app_info.window_width = float(width);
    m_app_info.window_height = float(height);

    simplerand::from_seed(static_cast<unsigned>(std::time(nullptr)));

    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
            printf("%s => Failed to initialize SDL: %s\n", FUNCTION_NAME, SDL_GetError());
            return -1;
        }

        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
        if (linear_filter) {
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                return -1;
            }
        }
        
        Uint32 flags = (SDL_WINDOW_SHOWN/* | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI*/);
        m_window = SDL_CreateWindow("AppCoreWeb", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
        if (!m_window) {
            printf("%s => Failed to create Window: %s\n", FUNCTION_NAME, SDL_GetError());
            return -1;
        }

        flags = (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        m_renderer = SDL_CreateRenderer(m_window, -1, flags);
        if (!m_renderer) {
            printf("%s => Failed to create Renderer: %s\n", FUNCTION_NAME, SDL_GetError());
            return -1;
        }

        if (SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND) != 0) {
            return -1;
        }
        
        const int img_loaders = (IMG_INIT_JPG | IMG_INIT_PNG);
        if ((IMG_Init(img_loaders) & img_loaders) != img_loaders) {
            printf("%s => Failed to initialize SDL_image: %s\n", FUNCTION_NAME, IMG_GetError());
            return -1;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("%s => Failed to initialize SDL_mixer: %s\n", FUNCTION_NAME, Mix_GetError());
            return -1;
        }

        if (TTF_Init() != 0) {
            printf("%s => Failed to initialize SDL_ttf: %s\n", FUNCTION_NAME, TTF_GetError());
            return -1;
        }
    }

    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
        ImGui_ImplSDLRenderer2_Init(m_renderer);
    }
    return 0;
}

int AppCore::run() {
    while (!m_quit) {
        this->update();
        this->render();
    }
    return 0;
}

void AppCore::update() {
    SDL_Event evt = {0};
    while (SDL_PollEvent(&evt)) {
        ImGui_ImplSDL2_ProcessEvent(&evt);
        
        if (evt.type == SDL_QUIT) {
            m_quit = true;
            break;
        }
    }

    if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED) {
        SDL_Delay(10);
    }
}

void AppCore::render() {
    {
        ImGuiIO &io = ImGui::GetIO();

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
        this->render_imgui();

        ImGui::Render();
        SDL_RenderSetScale(m_renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        SDL_RenderClear(m_renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer);
    }
    
    SDL_RenderPresent(m_renderer);
}

void AppCore::render_imgui() {
    if (m_show_demo_window) {
        ImGui::ShowDemoWindow(&m_show_demo_window);
    }

    {
        ImGui::Begin("Hello, world!");
        ImGui::Checkbox("Demo Window", &m_show_demo_window);

        {
            SDL_version compiled, linked;

            SDL_VERSION(&compiled);
            SDL_GetVersion(&linked);
            ImGui::Text("SDL: %d.%d.%d(C %u.%u.%u, L %u.%u.%u)",
                SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL,
                compiled.major, compiled.minor, compiled.patch,
                linked.major, linked.minor, linked.patch,
            );
            ImGui::Text("ImGui: %s", IMGUI_VERSION);
        }

        ImGui::Text("fps: %d", m_app_info.stats.fps);
        ImGui::End();
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