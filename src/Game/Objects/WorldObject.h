#pragma once

#include <vmath.h>
#include "../../Interface/ControlState.h"


class WorldObject {
public:
    WorldObject(vmath::vec2 size, vmath::vec2 position, vmath::vec2 velocity, float angle);
    vmath::vec2 getSize() const;
    vmath::vec2 getPosition() const;
    vmath::vec2 getVelocity() const;
    float getAngle() const;

    void setPosition(const vmath::vec2& position);

protected:
    vmath::vec2 size;
    vmath::vec2 position;
    vmath::vec2 velocity;
    float angle{0};

    static float calculateAngle(vmath::vec2& dir);
};
