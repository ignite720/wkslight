#pragma once

struct Ball final : public Actor {
    static constexpr float SIZE = 32.0f;

    Ball(SDL_Renderer *renderer, float x, float y);

    virtual void update(const AppCore *app_core) override;
    virtual void render() override;

public:
    void update_collision(const SDL_FRect *paddle_rect);

private:
    std::unique_ptr<Texture> m_texture;
    int m_move_state = MOVE_STATE_NONE;
};