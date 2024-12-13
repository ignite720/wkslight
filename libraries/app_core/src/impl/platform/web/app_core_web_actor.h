#pragma once

struct Actor {
    Actor(SDL_Renderer *renderer);
    virtual ~Actor() = default;

    virtual void update() {}
    virtual void render() = 0;

    void set_velocity(float vx, float vy);

protected:
    SDL_Renderer *m_renderer = nullptr;
    SDL_FRect m_dst_rect = {};
    Vector2 m_velocity;
};