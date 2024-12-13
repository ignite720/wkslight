#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Ball::Ball(SDL_Renderer *renderer)
    : Actor(renderer) {
    m_texture = std::make_unique<Texture>(renderer, "assets/ball.png");

    m_dst_rect.x = 0;
    m_dst_rect.y = 0;
    m_dst_rect.w = m_texture->get_width();
    m_dst_rect.h = m_texture->get_height();

    m_velocity.x = utils::random::gen_range(-0.1f, 0.1f);
    m_velocity.y = 0.1f;
}

void Ball::update() {
    Actor::update();
}

void Ball::render() {
    utils::fill_rect_with_texture(m_renderer, &m_dst_rect, m_texture->get_raw_texture());
}

#endif