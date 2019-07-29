#pragma once

#include <vmath.h>
#include "Position.h"
#include "ControlState.h"


enum VelocityUpdate {
    INCREASE,
    DECREASE,
    TO_ZERO
};

class Player {
public:
    Player(float x, float y, float v_x, float v_y, const vmath::vec2& dir);

    Position getNextPosition(ControlState controlState, double deltaTime);
    Position getPosition();
    void setPosition(Position new_position);

    float getAngle();

private:
    Position position;
    float x_velocity{};
    float y_velocity{};
    vmath::vec2 direction;
    float angle;

    static float updateVelocity(float velocity, VelocityUpdate vUpdate, double deltaTime);
    static float calculateAngle(vmath::vec2& dir);

    void updateXVelocity(VelocityUpdate vUpdate, double deltaTime);
    void updateYVelocity(VelocityUpdate vUpdate, double deltaTime);
};
