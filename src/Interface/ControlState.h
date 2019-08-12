#pragma once

#include <vmath.h>


class ControlState {
public:
    ControlState() = default;
    void setMovementDirection(float xAxis, float yAxis);
    void setBulletDirection(float xAxis, float yAxis);

    vmath::vec2 getMovementDirection() const;
    float getMovementMagnitude() const;
    vmath::vec2 getBulletDirection() const;

private:
    vmath::vec2 movementDirection;
    vmath::vec2 bulletDirection;
};
