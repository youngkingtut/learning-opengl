#pragma once

#include <glm/glm.hpp>
#include <string>

class GameControlState {
public:
    GameControlState() = default;
    void setMovementDirection(float xAxis, float yAxis);
    void setBulletDirection(float xAxis, float yAxis);
    void setPausePress(bool status);
    void setPauseRelease(bool status);

    glm::vec2 getMovementDirection() const;
    float getMovementMagnitude() const;
    glm::vec2 getBulletDirection() const;
    bool getPausePress() const;
    bool getPauseRelease() const;

    std::string toString() const;

private:
    glm::vec2 movementDirection;
    glm::vec2 bulletDirection;
    bool pausePress{false};
    bool pauseRelease{false};
};
