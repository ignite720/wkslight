#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Actor::Actor(SDL_Renderer *renderer)
    : m_renderer(renderer) {

}

void Actor::update() {
    m_dst_rect.x += m_velocity.x;
    m_dst_rect.y += m_velocity.y;
}

void Actor::set_velocity(float vx, float vy) {
    if (m_velocity.x != 0.0f && m_velocity.y != 0.0f) {
        m_velocity = Vector2::normalize(m_velocity);
    }
}

#endif