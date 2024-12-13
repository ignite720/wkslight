#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Player::Player(SDL_Renderer *renderer)
    : Actor(renderer) {
    m_dst_rect = { 0, 0, 100, 10 };
}

void Player::update() {
    m_velocity.x = m_velocity.y = 0.0f;
    #if 0
    if (m_move_state & MOVE_STATE_UP) {
        m_velocity.y = -MOVE_DELTA;
    }
    if (m_move_state & MOVE_STATE_DOWN) {
        m_velocity.y = +MOVE_DELTA;
    }
    #endif
    if (m_move_state & MOVE_STATE_LEFT) {
        m_velocity.x = -MOVE_DELTA;
    }
    if (m_move_state & MOVE_STATE_RIGHT) {
        m_velocity.x = +MOVE_DELTA;
    }

    if (m_velocity.x != 0.0f && m_velocity.y != 0.0f) {
        m_velocity = Vector2::normalize(m_velocity);
    }

    m_dst_rect.x += m_velocity.x;
    m_dst_rect.y += m_velocity.y;
}

void Player::render() {
    utils::fill_rect_with_color(m_renderer, &m_dst_rect, SDL_Color { 205, 205, 205, 255 });
}

#endif