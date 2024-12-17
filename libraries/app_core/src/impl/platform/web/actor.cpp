#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Actor::Actor(AppCore *app_core, float x, float y)
    : WebObject(app_core) {
    m_dst_rect.x = x;
    m_dst_rect.y = y;
}

void Actor::update(float dt) {
    if (m_dead) {
        if (utils::sdl::now() >= m_respawn_time) {
            this->on_spawn(dt);
        }
    } else {
        m_dst_rect.x += m_velocity.x;
        m_dst_rect.y += m_velocity.y;
    }
}

void Actor::on_spawn(float dt) {
    m_dead = false;
}

void Actor::set_dead() {
    m_dead = true;
    m_respawn_time = std::numeric_limits<float>::max();
}

void Actor::respawn() {
    if (!m_dead) {
        return;
    }
    
    m_respawn_time = (utils::sdl::now() + RESPAWN_DELAY);
}

#endif