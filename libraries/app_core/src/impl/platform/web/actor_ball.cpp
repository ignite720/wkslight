#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Ball::Ball(SDL_Renderer *renderer, const AppCore *app_core)
    : Actor(renderer, 0.0f, 0.0f) {
    m_texture = std::make_unique<Texture>(renderer);
    auto _ret = m_texture->load_from_file("assets/textures/ball.png");
    this->set_rect_size(m_texture->get_width(), m_texture->get_height());

    this->reset(app_core);
}

void Ball::update(const AppCore *app_core) {
    if ((m_dst_rect.x < 0.0f) || ((m_dst_rect.x + m_dst_rect.w) > app_core->get_window_width())) {
        app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_BOUNCE);
        m_velocity.x = -m_velocity.x;
    }
    if (m_dst_rect.y < 0.0f) {
        app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_BOUNCE);
        m_velocity.y = -m_velocity.y;
    }

    if ((m_dst_rect.y + m_dst_rect.h) > app_core->get_window_height()) {
        this->reset(app_core);
    }
    
    this->set_velocity(m_velocity);
    Actor::update(app_core);
}

void Ball::render() {
    m_texture->render(&m_dst_rect);
}

void Ball::reset(const AppCore *app_core) {
    m_dst_rect.x = simplerand::gen_range(0.0f, app_core->get_window_width() - Ball::SIZE);
    m_dst_rect.y = 0.0f;

    m_velocity.x = (simplerand::gen() > 0.5f ? 2.0f : -2.0f);
    m_velocity.y = simplerand::gen_range(2.0f, 3.0f);
}

void Ball::update_collision(const AppCore *app_core, const SDL_FRect *paddle_rect) {
    if (SDL_HasIntersectionF(&m_dst_rect, paddle_rect)) {
        app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_HIT);
        m_velocity.y = -m_velocity.y;

        auto p1 = utils::to_center_point(paddle_rect);
        auto p2 = utils::to_center_point(&m_dst_rect);
        //m_velocity.x = ((p2.x - p1.x) * 0.05f);
    }
}

#endif