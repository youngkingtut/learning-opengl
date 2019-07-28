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
    Player(float x, float y, float v_x, float v_y, const vmath::vec3& dir);
    void updateXVelocity(VelocityUpdate vUpdate, double deltaTime);
    void updateYVelocity(VelocityUpdate vUpdate, double deltaTime);
    void updatePosition(Position position);
    Position getNextPosition(ControlState controlState, double deltaTime);

    Position getPosition();
    float getXVelocity();
    float getYVelocity();

private:
    Position position;
    float x_velocity{};
    float y_velocity{};
    vmath::vec3 direction;

    static float UpdateVelocity(float velocity, VelocityUpdate vUpdate, double deltaTime);
};
