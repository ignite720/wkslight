#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Ball::Ball(SDL_Renderer *renderer, float x, float y)
    : Actor(renderer, x, y) {
    m_texture = std::make_unique<Texture>(renderer, "assets/ball.png");

    m_dst_rect.w = m_texture->get_width();
    m_dst_rect.h = m_texture->get_height();

    m_velocity.x = simplerand::gen_range(-0.5f, 0.5f);
    m_velocity.y = simplerand::gen_range(0.2f, 1.2f);
}

void Ball::update(const AppCore *app_core) {
    if ((m_dst_rect.x <= 0.0f) || ((m_dst_rect.x + m_dst_rect.w) >= app_core->get_window_width())) {
        v.x = -v.x;
    }
    if ((m_dst_rect.y <= 0.0f) || ((m_dst_rect.y + m_dst_rect.h) >= app_core->get_window_height())) {
        v.y = -v.y;
    }

    Actor::update(app_core);
}

void Ball::render() {
    utils::fill_rect_with_texture(m_renderer, &m_dst_rect, m_texture->get_raw_texture());
}

#endif