#pragma once

#include <vmath.h>

enum VelocityUpdate {
    INCREASE,
    INCREASE_TO_ZERO,
    DECREASE,
    DECREASE_TO_ZERO,
    ZERO
};

class Player {
public:
    void initialize(float x, float y, float v_x, float v_y, const vmath::vec3& dir);
    void updateXVelocity(VelocityUpdate vUpdate, double factor);
    void updateYVelocity(VelocityUpdate vUpdate, double factor);
    void updatePosition(double deltaTime);

    float getXPosition();
    float getYPosition();
    float getXVelocity();
    float getYVelocity();

private:
    float x_position;
    float y_position;
    float x_velocity;
    float y_velocity;
    vmath::vec3 direction;

    static float UpdateVelocity(float velocity, VelocityUpdate vUpdate, double factor);
};
