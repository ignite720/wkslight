#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Paddle::Paddle(SDL_Renderer *renderer, const AppCore *app_core)
    : Actor(renderer, 0.0f, app_core->get_window_height() - Paddle::HEIGHT) {
    this->set_rect_size(WIDTH, HEIGHT);
}

void Paddle::update(const AppCore *app_core) {
    Vector2 v;
    if ((m_move_state & MOVE_STATE_LEFT) && ((m_dst_rect.x - MOVE_DELTA) > 0.0f)) {
        v.x = -MOVE_DELTA;
    }
    if ((m_move_state & MOVE_STATE_RIGHT) && ((m_dst_rect.x + m_dst_rect.w + MOVE_DELTA) < app_core->get_window_width())) {
        v.x = +MOVE_DELTA;
    }
    
    this->set_velocity(v);
    Actor::update(app_core);
}

void Paddle::render() {
    utils::sdl::fill_rect_with_color(m_renderer, &m_dst_rect, SDL_Color { 205, 205, 205, 255 });
}

#endif