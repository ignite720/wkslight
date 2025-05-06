#include "pch.h"

#if !TARGET_PLATFORM_ANDROID
#include "app_core/actor.h"
#include "app_core/utils.h"

Actor::Actor(AppCore &app_core, float x, float y)
    : AppCoreObj(app_core) {
    this->set_rect_left_top(x, y);
}

void Actor::update(float dt) {
    if (m_dead) {
        if (utils::sdl::now() >= m_respawn_time) {
            this->on_spawn(dt);
        }
        return;
    }

    m_dst_rect = this->rect_predict();
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