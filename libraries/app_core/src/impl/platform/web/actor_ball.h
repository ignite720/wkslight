#pragma once

struct Ball final : public Actor {
    static constexpr auto SIZE = 32.0f;
    static constexpr auto MOVE_DELTA = 50.0f;

    Ball(AppCore *app_core);

    virtual void update(float dt) override;
    virtual void render() override;

    virtual void on_spawn(float dt) override;

public:
    bool update_collision(float dt, const SDL_FRect *paddle_rect);

private:
    std::unique_ptr<Texture> m_texture;
};