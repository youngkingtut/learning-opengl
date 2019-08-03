#pragma once

#include <vmath.h>


class ControlState {
public:
    ControlState() = default;
    void setMovementDirection(float xAxis, float yAxis);

    vmath::vec2 getMovementDirection() const;
    float getMovementMagnitude() const;

private:
    vmath::vec2 movementDirection;
};
