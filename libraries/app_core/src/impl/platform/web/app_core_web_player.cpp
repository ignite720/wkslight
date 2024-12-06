#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

void Player::init(SDL_Renderer *renderer) {
    m_texture = std::make_unique<Texture>();
    m_texture->load_from_file(renderer, "assets/player.png");

    m_dst_rect.x = 0;
    m_dst_rect.y = 0;
    m_dst_rect.w = m_texture->get_width();
    m_dst_rect.h = m_texture->get_height();
}

void Player::update() {
    m_velocity.x = m_velocity.y = 0.0f;
    if (m_move_state & MOVE_STATE_UP) {
        m_velocity.y = -MOVE_DELTA;
    }
    if (m_move_state & MOVE_STATE_DOWN) {
        m_velocity.y = +MOVE_DELTA;
    }
    if (m_move_state & MOVE_STATE_LEFT) {
        m_velocity.x = -MOVE_DELTA;
    }
    if (m_move_state & MOVE_STATE_RIGHT) {
        m_velocity.x = +MOVE_DELTA;
    }

    if (m_velocity.x != 0.0f && m_velocity.y != 0.0f) {
        m_velocity = vec2::normalize(m_velocity);
    }

    m_dst_rect.x += m_velocity.x;
    m_dst_rect.y += m_velocity.y;
}

void Player::render(SDL_Renderer *renderer) {
    utils::fill_rect_with_texture(renderer, &m_dst_rect, m_texture->get_raw_texture());
}

#endif