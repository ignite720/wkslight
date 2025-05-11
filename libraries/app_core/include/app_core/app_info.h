#pragma once

struct AppInfo {
    float window_width = 0.0f;
    float window_height = 0.0f;
    bool linear_filter = false;
    float auto_close_timer = 0.0f;

    bool quit = false;
    bool show_demo_window = false;

    struct Config {
        bool logger_verbose = false;
    } config;

    struct GameSave {
        int high_score = 0;
    } gamesave;

    struct Stats {
        float now = 0.0f;
        float last_time = 0.0f;

        float delta_time = 0.0f;
        int fps = 0;

        struct Staging {
            int frames_accumulated = 0;
            float time_accumulated = 0.0f;
        } staging;
    } stats;

    struct GameInfo {
        bool game_over = true;
        bool stats_ready = false;
        bool paddle_friction = false;

        struct Stats {
            int num_rounds = 0;
            int score = 0;
        } stats;
    } game_info;
};