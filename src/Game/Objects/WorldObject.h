#pragma once

#include "../../Interface/ControlState.h"
#include "../GameState.h"


class WorldObject {
public:
    WorldObject(const glm::vec2&  size, const glm::vec2&  position, const glm::vec2&  velocity, const float &angle);
    bool shouldRemove() const;
    glm::vec2 getPosition() const;
    glm::vec2 getSize() const;
    float getAngle() const;
    void removeObject();

    virtual void setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) = 0;

protected:
    glm::vec2 size;
    glm::vec2 position;
    glm::vec2 velocity;
    float angle{0};
    bool remove{false};

    static float calculateAngle(glm::vec2& dir);
};
