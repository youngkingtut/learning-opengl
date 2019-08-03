#include "ControlState.h"


void ControlState::setMovementDirection(float x, float y) {
    movementDirection = vmath::vec2(x, -y);
}

vmath::vec2 ControlState::getMovementDirection() const {
    return movementDirection;
}

float ControlState::getMovementMagnitude() const {
    return vmath::length(movementDirection);
}
