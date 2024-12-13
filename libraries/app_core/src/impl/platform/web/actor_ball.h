#pragma once

struct Ball final : public Actor {
    Ball(SDL_Renderer *renderer);

    virtual void update(const AppCore *app_core) override;
    virtual void render() override;

private:
    std::unique_ptr<Texture> m_texture;
    int m_move_state = MOVE_STATE_NONE;
};