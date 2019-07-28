#pragma once

#include <vmath.h>
#include "Position.h"

enum VelocityUpdate {
    INCREASE,
    DECREASE,
    TO_ZERO
};

class Player {
public:
    Player() = default;
    void initialize(float x, float y, float v_x, float v_y, const vmath::vec3& dir);
    void updateXVelocity(VelocityUpdate vUpdate, double factor);
    void updateYVelocity(VelocityUpdate vUpdate, double factor);
    void updatePosition(Position position);
    Position getNextPosition(double deltaTime);

    float getXPosition();
    float getYPosition();
    float getXVelocity();
    float getYVelocity();

private:
    Position position;
    float x_velocity{};
    float y_velocity{};
    vmath::vec3 direction;

    static float UpdateVelocity(float velocity, VelocityUpdate vUpdate, double factor);
};
