#pragma once

#include <glm/glm.hpp>

class ControlState {
public:
    ControlState() = default;
    void setMovementDirection(float xAxis, float yAxis);
    void setBulletDirection(float xAxis, float yAxis);

    glm::vec2 getMovementDirection() const;
    float getMovementMagnitude() const;
    glm::vec2 getBulletDirection() const;

private:
    glm::vec2 movementDirection;
    glm::vec2 bulletDirection;
};
