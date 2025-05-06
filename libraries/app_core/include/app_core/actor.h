#pragma once

#include "app_core/app_core_obj.h"

class Actor : public AppCoreObj {
public:
    static constexpr auto RESPAWN_DELAY = 1.0f;

    Actor(AppCore &app_core, float x, float y);

public:
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

    const float2f & velocity_as_ref() const { return m_velocity; }
    float2f & velocity_as_mut() { return m_velocity; }
    void set_velocity(const float2f &value) { m_velocity = value; }

    bool get_dead() const { return m_dead; }
    void set_dead();

public:
    SDL_FRect rect_predict(int num_frames = 1) const {
        auto rect_dup = this->rect_as_ref();
        for (int i = 0; i < num_frames; ++i) {
            rect_dup.x += m_velocity.x;
            rect_dup.y += m_velocity.y;
        }
        return rect_dup;
    }

    void respawn();

private:
    SDL_FRect m_dst_rect = {};
    float2f m_velocity = {};

private:
    bool m_dead = false;
    float m_respawn_time = 0.0f;
};