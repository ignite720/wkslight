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
}

#endif