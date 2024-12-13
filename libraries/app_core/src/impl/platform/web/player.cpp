#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Player::Player(SDL_Renderer *renderer)
    : Actor(renderer) {
    m_dst_rect = { 0, 0, 60, 10 };
}

void Player::update() {
    Vector2 v;
    #if 0
    if (m_move_state & MOVE_STATE_UP) {
        v.y = -MOVE_DELTA;
    }
    if (m_move_state & MOVE_STATE_DOWN) {
        v.y = +MOVE_DELTA;
    }
    #endif
    if (m_move_state & MOVE_STATE_LEFT) {
        v.x = -MOVE_DELTA;
    }
    if (m_move_state & MOVE_STATE_RIGHT) {
        v.x = +MOVE_DELTA;
    }
    
    this->set_velocity(v);
    Actor::update();
}

void Player::render() {
    utils::fill_rect_with_color(m_renderer, &m_dst_rect, SDL_Color { 205, 205, 205, 255 });
}

#endif