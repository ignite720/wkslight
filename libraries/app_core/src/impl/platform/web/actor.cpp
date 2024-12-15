#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Actor::Actor(AppCore *app_core, float x, float y)
    : WebObject(app_core) {
    m_dst_rect.x = x;
    m_dst_rect.y = y;
}

void Actor::update(float dt) {
    m_dst_rect.x += m_velocity.x;
    m_dst_rect.y += m_velocity.y;

    if (utils::sdl::now() >= m_respawn_time) {
        m_dead = false;
        this->on_spawn(dt);
    }
}

void Actor::set_dead() {
    m_dead = true;
    m_respawn_time = (utils::sdl::now() + 5.0f);
}

#endif