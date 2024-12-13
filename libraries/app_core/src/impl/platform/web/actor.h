#pragma once

struct Actor {
    Actor(SDL_Renderer *renderer, float x, float y);
    virtual ~Actor() = default;

    virtual void update(const AppCore *app_core);
    virtual void render() = 0;

    const SDL_FRect * get_rect() const { return &m_dst_rect; }
    void set_velocity(const Vector2 &value);

protected:
    SDL_Renderer *m_renderer = nullptr;
    SDL_FRect m_dst_rect = {};
    Vector2 m_velocity;
};