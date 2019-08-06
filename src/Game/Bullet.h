#pragma once

#include <vmath.h>

#include "../Interface/ControlState.h"


class Bullet {
public:
    Bullet(vmath::vec2 size, vmath::vec2 position, vmath::vec2 velocity, float angle);
    Bullet(vmath::vec2 size, vmath::vec2 direction, vmath::vec2 position);
    vmath::vec2 setNextPosition(const ControlState &controlState, double deltaTime);
    vmath::vec2 getSize() const;
    vmath::vec2 getPosition() const;
    float getAngle() const;

private:
    vmath::vec2 size;
    vmath::vec2 position;
    vmath::vec2 velocity;
    float angle;

    static float calculateAngle(vmath::vec2& dir);
};
