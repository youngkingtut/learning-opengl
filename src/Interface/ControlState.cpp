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

void ControlState::setBulletDirection(float xAxis, float yAxis) {
    bulletDirection = vmath::vec2(xAxis, yAxis);
}

vmath::vec2 ControlState::getBulletDirection() const {
    return bulletDirection;
}
