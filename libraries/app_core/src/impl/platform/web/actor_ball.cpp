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
        m_velocity.x = -m_velocity.x;
    }
    if ((m_dst_rect.y <= 0.0f) || ((m_dst_rect.y + m_dst_rect.h) >= app_core->get_window_height())) {
        m_velocity.y = -m_velocity.y;
    }
    
    Actor::update(app_core);
}

void Ball::render() {
    utils::fill_rect_with_texture(m_renderer, &m_dst_rect, m_texture->get_raw_texture());
}

void Ball::update_collision(const SDL_FRect *paddle_rect) {
    if (SDL_HasIntersectionF(&m_dst_rect, paddle_rect)) {
        m_velocity.y = -m_velocity.y;

        auto p1 = utils::to_center_point(&m_dst_rect);
        auto p2 = utils::to_center_point(paddle_rect);
        m_velocity.x = ((p1.x - p2.x) * 0.05f);
    }
}

#endif