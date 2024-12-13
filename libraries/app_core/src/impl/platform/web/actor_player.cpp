#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Player::Player(SDL_Renderer *renderer, float x, float y)
    : Actor(renderer, x, y) {
    m_dst_rect = { 0.0f, 0.0f, WIDTH, HEIGHT };
}

void Player::update(const AppCore *app_core) {
    Vector2 v;
    if ((m_move_state & MOVE_STATE_LEFT) && ((m_dst_rect.x - MOVE_DELTA) > 0)) {
        v.x = -MOVE_DELTA;
    }
    if ((m_move_state & MOVE_STATE_RIGHT) && (m_dst_rect.x < (app_core->get_window_width() - MOVE_DELTA))) {
        v.x = +MOVE_DELTA;
    }
    
    this->set_velocity(v);
    Actor::update(app_core);
}

void Player::render() {
    utils::fill_rect_with_color(m_renderer, &m_dst_rect, SDL_Color { 205, 205, 205, 255 });
}

#endif