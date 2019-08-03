#pragma once

#include <vmath.h>
#include "../Interface/ControlState.h"


enum VelocityUpdate {
    INCREASE,
    TO_ZERO
};

class Player {
public:
    explicit Player(vmath::vec2 size);

    void setPosition(vmath::vec2 position);

    vmath::vec2 getSize() const;
    vmath::vec2 getPosition() const;
    vmath::vec2 setNextPosition(const ControlState &controlState, double deltaTime);
    float getAngle() const;

private:
    vmath::vec2 size;
    vmath::vec2 position;
    vmath::vec2 velocity;
    float angle;

    static float updateVelocity(float velocity, VelocityUpdate vUpdate, double deltaTime);
    static float calculateAngle(vmath::vec2& dir);

    void updateXVelocity(VelocityUpdate vUpdate, double deltaTime);
    void updateYVelocity(VelocityUpdate vUpdate, double deltaTime);
};
