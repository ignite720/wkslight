#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Ball::Ball(AppCore *app_core)
    : Actor(app_core, 0.0f, 0.0f) {
    m_texture = std::make_unique<Texture>(app_core);
    auto _ret = m_texture->load_from_file("assets/textures/ball.png");
    m_texture->set_blend_mode(SDL_BLENDMODE_BLEND);

    this->set_rect_size(m_texture->get_width(), m_texture->get_height());
    this->set_dead();
}

void Ball::update(float dt) {
    if (m_app_core->app_info_as_ref().game_info.game_over) {
        return;
    }
    
    #if 0
    if (m_velocity.x == 0.0f && m_velocity.y == 0.0f) {
        this->reset(dt);
    }
    #endif

    if ((m_dst_rect.x < 0.0f) || ((m_dst_rect.x + m_dst_rect.w) > m_app_core->app_info_as_ref().window_width)) {
        m_app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_BOUNCE);
        m_velocity.x = -m_velocity.x;
    }
    if (m_dst_rect.y < 0.0f) {
        m_app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_BOUNCE);
        m_velocity.y = -m_velocity.y;
    }

    if (!this->get_dead() && (m_dst_rect.y + m_dst_rect.h) > m_app_core->app_info_as_ref().window_height) {
        m_app_core->app_info_as_mut().game_info.game_over = true;
        m_app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_LOSE);
        m_app_core->play_audio_music(ResourceBundle::AUDIO_MUSIC_INSERT_COIN);
        printf("YOU LOSE!\n");

        this->set_dead();
    }
    
    Actor::update(dt);
}

void Ball::render() {
    m_texture->render(&m_dst_rect);
}

void Ball::on_spawn(float dt) {
    Actor::on_spawn(dt);
    
    this->reset(dt);
    m_app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_COIN);
    m_app_core->play_audio_music(ResourceBundle::AUDIO_MUSIC_ITEM_SHOP);
}

bool Ball::update_collision(float dt, const SDL_FRect *paddle_rect) {
    if (SDL_HasIntersectionF(&m_dst_rect, paddle_rect)) {
        m_app_core->play_audio_clip(ResourceBundle::AUDIO_CLIP_HIT);
        printf("%s\n", consts::text::CONGRATULATIONS[simplerand::gen_range(0, static_cast<int>(COUNT_OF(consts::text::CONGRATULATIONS)))]);

        m_velocity.y = -m_velocity.y;
        if (m_app_core->app_info_as_ref().game_info.paddle_friction) {
            auto p1 = utils::sdl::to_center_point(paddle_rect);
            auto p2 = utils::sdl::to_center_point(&m_dst_rect);
            m_velocity.x = ((p2.x - p1.x) * 0.1f * MOVE_DELTA * dt);
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