#pragma once

#include "app_core/actor.h"

class Paddle : public Actor {
public:
    static constexpr auto WIDTH = 60.0f;
    static constexpr auto HEIGHT = 10.0f;
    static constexpr auto MOVE_DELTA = 500.0f;

public:
    Paddle(AppCore &app_core);
    
public:
    virtual void update(float dt) override;
    virtual void render() override;

public:
    int get_move_state() const { return m_move_state; }
    void set_move_state(int value) { m_move_state = value; }

private:
    int m_move_state = MOVE_STATE_NONE;
};