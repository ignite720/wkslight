#pragma once

#include "app_core/actor.h"
#include "app_core/texture.h"

class Ball : public Actor {
public:
    static constexpr auto MOVE_DELTA = 50.0f;
    static constexpr auto MOVE_SPEED_BASE = 5.0f;
    static constexpr auto MOVE_SPEED_BIAS = 0.5f;
    static constexpr auto ROTATION_SPEED = 100.0f;

public:
    Ball(AppCore &app_core);

public:
    virtual void update(float dt) override;
    virtual void render() override;

    virtual void on_spawn(float dt) override;

public:
    int get_flip() const { return m_flip; }
    void set_flip(int value) {
        m_flip = (value % (SDL_FLIP_VERTICAL + 1));
    }

public:
    bool update_collision(float dt, const SDL_FRect *paddle_rect);

private:
    std::unique_ptr<Texture> m_texture;
    float m_rotation = 0.0f;
    int m_flip = SDL_FLIP_NONE;
};