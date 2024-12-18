#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Paddle::Paddle(AppCore *app_core)
    : Actor(app_core, 0.0f, app_core->app_info_as_ref().window_height - HEIGHT) {
    this->set_rect_size(WIDTH, HEIGHT);
    this->set_dead();
}

void Paddle::update(float dt) {
    Actor::update(dt);

    if (m_app_core->app_info_as_ref().game_info.game_over) {
        return;
    }

    const auto move_delta = (MOVE_DELTA * dt);

    rtm::float2f v = {};
    if ((m_move_state & MOVE_STATE_LEFT) && ((this->rect_as_ref().x - move_delta) > 0.0f)) {
        v.x = -move_delta;
    }
    if ((m_move_state & MOVE_STATE_RIGHT) && ((this->rect_as_ref().x + this->rect_as_ref().w + move_delta) < m_app_core->app_info_as_ref().window_width)) {
        v.x = +move_delta;
    }

    this->set_velocity(v);
}

void Paddle::render() {
    const auto color = (m_app_core->app_info_as_ref().game_info.paddle_friction ? consts::colors::RED : consts::colors::SILVER );
    utils::sdl::fill_rect_with_color(WEB_OBJECT_GET_RENDERER, &this->rect_as_ref(), color);
}

void Paddle::on_spawn(float dt) {
    Actor::on_spawn(dt);

    this->set_rect_left_top(0.0f, m_app_core->app_info_as_ref().window_height - HEIGHT);
    this->set_velocity({});
}

#endif