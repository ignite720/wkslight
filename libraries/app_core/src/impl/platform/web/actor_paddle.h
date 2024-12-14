#pragma once

struct Paddle final : public Actor {
    static constexpr float WIDTH = 60.0f;
    static constexpr float HEIGHT = 10.0f;
    static constexpr float MOVE_DELTA = 12.0f;

    struct Stats {
        int num_streaks = 0;
    };

    Paddle(SDL_Renderer *renderer, const AppCore *app_core);

    int get_move_state() const { return m_move_state; }
    void set_move_state(int value) { m_move_state = value; }

    Stats & stats_as_mut() { return m_stats; }

    virtual void update(const AppCore *app_core) override;
    virtual void render() override;

private:
    int m_move_state = MOVE_STATE_NONE;
    Stats m_stats;
};