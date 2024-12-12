#pragma once

struct Actor {
    Actor(SDL_Renderer *renderer);
    virtual ~Actor() = default;

    virtual void render() = 0;

protected:
    SDL_Renderer *m_renderer = nullptr;
    SDL_Rect m_dst_rect = {};
    vec2 m_velocity;
};