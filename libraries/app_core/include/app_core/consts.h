#pragma once

#if !TARGET_PLATFORM_ANDROID
enum MOVE_STATE {
    MOVE_STATE_NONE = 0,
    MOVE_STATE_UP = 1 << 0,
    MOVE_STATE_DOWN = 1 << 1,
    MOVE_STATE_LEFT = 1 << 2,
    MOVE_STATE_RIGHT = 1 << 3,
};

namespace consts {
    namespace anchor_point {
        static const auto LEFT_TOP = SDL_FPoint { 0.0f, 0.0f };
        static const auto RIGHT_TOP = SDL_FPoint { 1.0f, 0.0f };
        static const auto LEFT_BOTTOM = SDL_FPoint { 0.0f, 1.0f };
        static const auto RIGHT_BOTTOM = SDL_FPoint { 1.0f, 1.0f };
        static const auto CENTER = SDL_FPoint { 0.5f, 0.5f };
    }

    namespace colors {
        static const auto WHITE = SDL_Color { 255, 255, 255, 255 };
        static const auto BLACK = SDL_Color { 0, 0, 0, 255 };
        static const auto GRAY = SDL_Color { 128, 128, 128, 255 };

        static const auto RED = SDL_Color { 255, 0, 0, 0xff };
        static const auto GREEN = SDL_Color { 0, 255, 0, 0xff };
        static const auto BLUE = SDL_Color { 0, 0, 255, 0xff };

        static const auto YELLOW = SDL_Color { 255, 255, 0, 0xff };
        static const auto PURPLE = SDL_Color { 128, 0, 128, 0xff };
        static const auto ORANGE = SDL_Color { 255, 165, 0, 0xff };
        static const auto PINK = SDL_Color { 255, 192, 203, 0xff };
        static const auto CYAN = SDL_Color { 0, 255, 255, 0xff };
        static const auto BROWN = SDL_Color { 165, 42, 42, 0xff };
        static const auto TEAL = SDL_Color { 0, 128, 128, 0xff };
        static const auto SILVER = SDL_Color { 192, 192, 192, 0xff };
        static const auto GOLD = SDL_Color { 255, 215, 0, 0xff };
    }

    namespace text {
        static constexpr const char *const CONGRATULATIONS[] = {
            "AMAZING!",
            "BRAVO!",
            "EXCELLENT!",
            "FANTASTIC!",
            "GOOD JOB!",
            "GREAT JOB!",
            "GREAT WORK!",
            "IMPRESSIVE!",
            "INCREDIBLE!",
            "MARVELOUS!",
            "NICE!",
            "NICE JOB!",
            "OUTSTANDING!",
            "PHENOMENAL!",
            "SUPERB!",
            "WELL DONE!",
            "WELL PLAYED!",
        };

        static constexpr const char *const GAME_OVER_HINT = "PRESS [I] OR [SPACE] OR CLICK\nINSERT COIN TO CONTINUE!";
        static constexpr const char *const GAMESAVE_FILE_NAME = "gamesave001.dat";
    }

    static constexpr auto RESOLUTION_SCALE_FACTOR = 0.5f;
    static constexpr auto WINDOW_WIDTH = int(1920 * RESOLUTION_SCALE_FACTOR);
    static constexpr auto WINDOW_HEIGHT = int(1080 * RESOLUTION_SCALE_FACTOR);
}
#endif