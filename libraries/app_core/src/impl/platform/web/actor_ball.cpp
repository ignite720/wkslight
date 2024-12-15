#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Ball::Ball(AppCore *app_core)
    : Actor(app_core, 0.0f, 0.0f) {
    m_texture = std::make_unique<Texture>(app_core);
    auto _ret = m_texture->load_from_file("assets/textures/ball.png");
    m_texture->set_blend_mode(SDL_BLENDMODE_BLEND);

    this->set_rect_size(m_texture->get_width(), m_texture->get_height());
}

void Ball::update(float dt) {
    if (m_velocity.x == 0.0f && m_velocity.y == 0.0f) {
        this->reset(dt);
    }

    if ((m_dst_rect.x < 0.0f) || ((m_dst_rect.x + m_dst_rect.w) > m_app_core->app_info_as_ref().window_width)) {
        m_app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_BOUNCE);
        m_velocity.x = -m_velocity.x;
    }
    if (m_dst_rect.y < 0.0f) {
        m_app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_BOUNCE);
        m_velocity.y = -m_velocity.y;
    }

    if ((m_dst_rect.y + m_dst_rect.h) > m_app_core->app_info_as_ref().window_height) {
        this->reset(dt);
    }
    
    Actor::update(dt);
}

void Ball::render() {
    m_texture->render(&m_dst_rect);
}

bool Ball::update_collision(float dt, const SDL_FRect *paddle_rect) {
    if (SDL_HasIntersectionF(&m_dst_rect, paddle_rect)) {
        m_app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_HIT);
        m_velocity.y = -m_velocity.y;

        if (m_app_core->app_info_as_ref().game_info.paddle_friction) {
            auto p1 = utils::sdl::to_center_point(paddle_rect);
            auto p2 = utils::sdl::to_center_point(&m_dst_rect);
            m_velocity.x = ((p2.x - p1.x) * MOVE_DELTA * dt);
        }
        return true;
    }
    return false;
}

void Ball::reset(float dt) {
    m_dst_rect.x = simplerand::gen_range(0.0f, m_app_core->app_info_as_ref().window_width - Ball::SIZE);
    m_dst_rect.y = 0.0f;

    m_velocity.x = ((simplerand::gen() > 0.5f ? 5.0f : -5.0f) * MOVE_DELTA * dt);
    m_velocity.y = (simplerand::gen_range(4.0f, 6.0f) * MOVE_DELTA * dt);

    m_app_core->restart();
}

#endif