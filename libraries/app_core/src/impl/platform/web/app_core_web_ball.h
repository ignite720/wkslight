#pragma once

struct Ball final : public Actor {
    static constexpr int MOVE_DELTA = 2;

    Ball(SDL_Renderer *renderer);

    virtual void update() override;
    virtual void render() override;

private:
    std::unique_ptr<Texture> m_texture;
    int m_move_state = MOVE_STATE_NONE;
};