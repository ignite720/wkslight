#pragma once

struct Paddle final : public Actor {
    static constexpr float WIDTH = 60.0f;
    static constexpr float HEIGHT = 10.0f;
    static constexpr float MOVE_DELTA = 2.0f;

    Paddle(SDL_Renderer *renderer, float x, float y);

    int get_move_state() const { return m_move_state; }
    void set_move_state(int value) { m_move_state = value; }

    virtual void update(const AppCore *app_core) override;
    virtual void render() override;

private:
    std::unique_ptr<Texture> m_texture;
    int m_move_state = MOVE_STATE_NONE;
};