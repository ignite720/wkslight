#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Paddle::Paddle(AppCore *app_core)
    : Actor(app_core, 0.0f, app_core->app_info_as_ref().window_height - Paddle::HEIGHT) {
    this->set_rect_size(WIDTH, HEIGHT);
}

void Paddle::update(float dt) {
    if (m_app_core->app_info_as_ref().game_info.game_over) {
        return;
    }

    const auto move_delta = (MOVE_DELTA * dt);

    Vector2 v;
    if ((m_move_state & MOVE_STATE_LEFT) && ((m_dst_rect.x - move_delta) > 0.0f)) {
        v.x = -move_delta;
    }
    if ((m_move_state & MOVE_STATE_RIGHT) && ((m_dst_rect.x + m_dst_rect.w + move_delta) < m_app_core->app_info_as_ref().window_width)) {
        v.x = +move_delta;
    }

    m_velocity = v;
    Actor::update(dt);
}

void Paddle::render() {
    const auto color = (m_app_core->app_info_as_ref().game_info.paddle_friction ? consts::colors::RED : consts::colors::SILVER );
    utils::sdl::fill_rect_with_color(WEB_OBJECT_GET_RENDERER, &m_dst_rect, color);
}

#endif