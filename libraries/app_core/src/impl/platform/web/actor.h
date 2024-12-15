#pragma once

struct Actor : public WebObject {
    Actor(AppCore *app_core, float x, float y);
    virtual ~Actor() = default;

    virtual void update(float dt);
    virtual void render() = 0;

    const SDL_FRect * get_rect() const { return &m_dst_rect; }
    void set_rect_size(float width, float height) {
        m_dst_rect.w = width;
        m_dst_rect.h = height;
    }

protected:
    SDL_FRect m_dst_rect = {};
    Vector2 m_velocity;
};