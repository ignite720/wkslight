#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Actor::Actor(SDL_Renderer *renderer, float x, float y)
    : m_renderer(renderer) {
    m_dst_rect.x = x;
    m_dst_rect.y = y;
}

void Actor::update(const AppCore *app_core) {
    m_dst_rect.x += m_velocity.x;
    m_dst_rect.y += m_velocity.y;
}

#endif