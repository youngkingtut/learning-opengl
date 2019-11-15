#include "GameControlState.h"

#include <sstream>

void GameControlState::setMovementDirection(float x, float y) {
    movementDirection = glm::vec2(x, -y);
}

glm::vec2 GameControlState::getMovementDirection() const {
    return movementDirection;
}

float GameControlState::getMovementMagnitude() const {
    return glm::length(movementDirection);
}

void GameControlState::setBulletDirection(float xAxis, float yAxis) {
    bulletDirection = glm::vec2(xAxis, yAxis);
}

glm::vec2 GameControlState::getBulletDirection() const {
    return bulletDirection;
}

void GameControlState::setPausePress(bool status) {
    this->pausePress = status;
}

bool GameControlState::getPausePress() const {
    return this->pausePress;
}

void GameControlState::setPauseRelease(bool status) {
    this->pauseRelease = status;
}

bool GameControlState::getPauseRelease() const {
    return this->pauseRelease;
}

std::string GameControlState::toString() const {
    std::stringstream ss;

    ss << "MD(" << movementDirection.x << ", " << movementDirection.y << ") ";
    ss << "BD(" << bulletDirection.x << ", " << bulletDirection.y << ") ";

    return ss.str();
}
