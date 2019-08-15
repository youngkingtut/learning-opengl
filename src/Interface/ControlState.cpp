#include "ControlState.h"


void ControlState::setMovementDirection(float x, float y) {
    movementDirection = glm::vec2(x, -y);
}

glm::vec2 ControlState::getMovementDirection() const {
    return movementDirection;
}

float ControlState::getMovementMagnitude() const {
    return glm::length(movementDirection);
}

void ControlState::setBulletDirection(float xAxis, float yAxis) {
    bulletDirection = glm::vec2(xAxis, yAxis);
}

glm::vec2 ControlState::getBulletDirection() const {
    return bulletDirection;
}
