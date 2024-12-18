#pragma once

struct Actor : public WebObject {
    static constexpr auto RESPAWN_DELAY = 1.0f;

    Actor(AppCore *app_core, float x, float y);
    virtual ~Actor() = default;

    virtual void update(float dt);
    virtual void render() = 0;

    virtual void on_spawn(float dt);

public:
    const SDL_FRect & rect_as_ref() const { return m_dst_rect; }
    void set_rect_left_top(float x, float y) {
        m_dst_rect.x = x;
        m_dst_rect.y = y;
    }
    void set_rect_size(float width, float height) {
        m_dst_rect.w = width;
        m_dst_rect.h = height;
    }

    rtm::float2f & velocity_as_mut() { return m_velocity; }
    void set_velocity(const rtm::float2f &value) { m_velocity = value; }

    bool get_dead() const { return m_dead; }
    void set_dead();

public:
    void respawn();

private:
    SDL_FRect m_dst_rect = {};
    rtm::float2f m_velocity = {};

private:
    bool m_dead = false;
    float m_respawn_time = 0.0f;
};