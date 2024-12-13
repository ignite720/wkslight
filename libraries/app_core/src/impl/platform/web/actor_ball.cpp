#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Ball::Ball(SDL_Renderer *renderer)
    : Actor(renderer) {
    m_texture = std::make_unique<Texture>(renderer, "assets/ball.png");

    m_dst_rect.x = 0;
    m_dst_rect.y = 0;
    m_dst_rect.w = m_texture->get_width();
    m_dst_rect.h = m_texture->get_height();

    m_velocity.x = simplerand::gen_range(-0.5f, 0.5f);
    m_velocity.y = simplerand::gen_range(0.2f, 1.2f);
}

void Ball::update(const AppCore *app_core) {
    Actor::update(app_core);
}

void Ball::render() {
    utils::fill_rect_with_texture(m_renderer, &m_dst_rect, m_texture->get_raw_texture());
}

#endif