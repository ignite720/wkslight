#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Paddle::Paddle(AppCore *app_core)
    : Actor(app_core, 0.0f, app_core->app_info_as_ref().window_height - Paddle::HEIGHT) {
    this->set_rect_size(WIDTH, HEIGHT);
}

void Paddle::update() {
    Vector2 v;
    if ((m_move_state & MOVE_STATE_LEFT) && ((m_dst_rect.x - MOVE_DELTA) > 0.0f)) {
        v.x = -MOVE_DELTA;
    }
    if ((m_move_state & MOVE_STATE_RIGHT) && ((m_dst_rect.x + m_dst_rect.w + MOVE_DELTA) < m_app_core->app_info_as_ref().window_width)) {
        v.x = +MOVE_DELTA;
    }
    
    this->set_velocity(v);
    Actor::update();
}

void Paddle::render() {
    auto color = (m_app_core->app_info_as_ref().game_info.paddle_friction ? consts::colors::RED : consts::colors::SILVER );
    utils::sdl::fill_rect_with_color(WEB_OBJECT_GET_RENDERER, &m_dst_rect, color);
}

#endif