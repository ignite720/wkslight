#pragma once

struct Actor : public WebObject {
    Actor(AppCore *app_core, float x, float y);
    virtual ~Actor() = default;

    virtual void update(float dt);
    virtual void render() = 0;

    virtual void on_spawn(float dt);

public:
    const SDL_FRect * get_rect() const { return &m_dst_rect; }
    void set_rect_size(float width, float height) {
        m_dst_rect.w = width;
        m_dst_rect.h = height;
    }

    bool get_dead() const { return m_dead; }
    void set_dead();

public:
    void respawn();

protected:
    SDL_FRect m_dst_rect = {};
    Vector2 m_velocity;

private:
    bool m_dead = false;
    float m_respawn_time = 0.0f;
};