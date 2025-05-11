#include "pch.h"

#if !TARGET_PLATFORM_ANDROID
#include "app_core/ball.h"
#include "app_core/app_core.h"
#include "app_core/resource_bundle.h"

#include <wkstk/simplerand.hpp>

Ball::Ball(AppCore &app_core)
    : Actor(app_core, app_core.app_info_as_ref().window_width * 0.5f, app_core.app_info_as_ref().window_height * 0.2f) {
    m_texture = std::make_unique<Texture>(app_core);
    auto ret = m_texture->load_from_file("assets/textures/ball.png");
    if (ret) {
        m_texture->set_blend_mode(SDL_BLENDMODE_BLEND);
    }

    this->set_rect_size(float(m_texture->get_width()), float(m_texture->get_height()));
    this->set_dead();
}

void Ball::update(float dt) {
    Actor::update(dt);

    if (this->app_core_as_mut_ptr()->app_info_as_ref().game_info.game_over) {
        return;
    }

    if ((this->rect_as_ref().x < 0.0f) || ((this->rect_as_ref().x + this->rect_as_ref().w) > this->app_core_as_mut_ptr()->app_info_as_ref().window_width)) {
        this->velocity_as_mut().x = -this->velocity_as_ref().x;
        this->app_core_as_mut_ptr()->play_audio_clip(ResourceBundle::AUDIO_CLIP_BOUNCE);
    }
    if (this->rect_as_ref().y < 0.0f) {
        this->velocity_as_mut().y = -this->velocity_as_ref().y;
        this->app_core_as_mut_ptr()->play_audio_clip(ResourceBundle::AUDIO_CLIP_BOUNCE);
    }

    if (!this->get_dead()) {
        m_rotation = std::fmod(m_rotation + ROTATION_SPEED * dt, 360.0f);

        if ((this->rect_as_ref().y + this->rect_as_ref().h) > this->app_core_as_mut_ptr()->app_info_as_ref().window_height) {
            this->app_core_as_mut_ptr()->app_info_as_mut().game_info.game_over = true;
            this->app_core_as_mut_ptr()->play_audio_clip(ResourceBundle::AUDIO_CLIP_LOSE);
            this->app_core_as_mut_ptr()->play_audio_music(ResourceBundle::AUDIO_MUSIC_INSERT_COIN);
            printf("YOU LOSE!\n");

            this->set_dead();
        }
    }
}

void Ball::render() {
    m_texture->render(&this->rect_as_ref(), nullptr, m_rotation, nullptr, static_cast<SDL_RendererFlip>(m_flip));
}

void Ball::on_spawn(float dt) {
    Actor::on_spawn(dt);
    
    this->set_rect_left_top(simplerand::gen_range(0.0f, this->app_core_as_mut_ptr()->app_info_as_ref().window_width - this->rect_as_ref().w), 0.0f);
    this->set_velocity({
        (simplerand::gen() > 0.5f ? 1 : -1) * simplerand::gen_range(MOVE_SPEED_BASE - MOVE_SPEED_BIAS, MOVE_SPEED_BASE + MOVE_SPEED_BIAS) * MOVE_DELTA * dt,
        simplerand::gen_range(MOVE_SPEED_BASE - MOVE_SPEED_BIAS, MOVE_SPEED_BASE + MOVE_SPEED_BIAS) * MOVE_DELTA * dt,
    });
    
    this->app_core_as_mut_ptr()->play_audio_clip(ResourceBundle::AUDIO_CLIP_COIN);
    this->app_core_as_mut_ptr()->play_audio_music(ResourceBundle::AUDIO_MUSIC_ITEM_SHOP);
}

bool Ball::update_collision(float dt, const SDL_FRect *paddle_rect) {
    const auto lam_calculate_velocity_scale = [=](float scale) {
        return std::log10(this->app_core_as_mut_ptr()->app_info_as_ref().game_info.stats.score + 1.0f) * scale + 1.0f;
    };

    if (this->app_core_as_mut_ptr()->app_info_as_ref().game_info.game_over) {
        return false;
    }

    const auto rect_for_test = this->rect_predict(2);
    if (!this->get_dead() && SDL_HasIntersectionF(&rect_for_test, paddle_rect)) {
        {
            this->app_core_as_mut_ptr()->app_info_as_mut().game_info.stats.score++;
            if (this->app_core_as_ptr()->app_info_as_ref().game_info.stats.score > this->app_core_as_ptr()->app_info_as_ref().gamesave.high_score) {
                this->app_core_as_mut_ptr()->app_info_as_mut().gamesave.high_score = this->app_core_as_ptr()->app_info_as_ref().game_info.stats.score;

                const auto &gamesave = this->app_core_as_ptr()->app_info_as_ref().gamesave;
                #if TARGET_PLATFORM_WEB
                utils::web::web_fetch_persist_file_store_t(consts::text::GAMESAVE_FILE_NAME, gamesave);
                #endif

                this->app_core_as_mut_ptr()->play_audio_clip(ResourceBundle::AUDIO_CLIP_NEW_RECORD);
                printf("CONGRATS! NEW RECORD!!\n");
            }

            this->velocity_as_mut().y = -this->velocity_as_ref().y;
            this->set_flip(m_flip + 1);
            if (this->app_core_as_mut_ptr()->app_info_as_ref().game_info.paddle_friction) {
                auto p1 = utils::sdl::to_center_point(paddle_rect);
                auto p2 = utils::sdl::to_center_point(&rect_for_test);
                this->velocity_as_mut().x = ((p2.x - p1.x) * 0.2f * MOVE_DELTA * dt);
            }

            {
                const auto v_scale = lam_calculate_velocity_scale(0.02f);
                this->velocity_as_mut().x *= v_scale;
                this->velocity_as_mut().y *= v_scale;

                if (this->app_core_as_mut_ptr()->app_info_as_ref().config.logger_verbose) {
                    printf("v_scale: %f, velocity: { %.f, %f }\n", v_scale, this->velocity_as_ref().x, this->velocity_as_ref().y);
                }
            }
        }
        this->app_core_as_mut_ptr()->play_audio_clip(ResourceBundle::AUDIO_CLIP_HIT);
        printf("%s\n", consts::text::CONGRATULATIONS[simplerand::gen_range(0, static_cast<int>(COUNTOF(consts::text::CONGRATULATIONS)))]);
        return true;
    }
    return false;
}
#endif