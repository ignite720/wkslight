#pragma once

struct Ball final : public Actor {
    static constexpr float SIZE = 32.0f;
    static constexpr float SPEED = 1.0f;

    Ball(AppCore *app_core);

    virtual void update(float dt) override;
    virtual void render() override;

public:
    void reset();
    bool update_collision(const SDL_FRect *paddle_rect);

private:
    std::unique_ptr<Texture> m_texture;
    int m_move_state = MOVE_STATE_NONE;
};