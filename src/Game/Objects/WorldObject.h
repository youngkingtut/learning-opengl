#pragma once

#include "../../Interface/ControlState.h"
#include "../GameState.h"


class WorldObject {
public:
    WorldObject(const glm::vec2 &position, const glm::vec2 &velocity, const glm::vec2 &direction);
    bool shouldRemove() const;
    glm::vec2 getPosition() const;
    glm::vec2 getDirection() const;
    void removeObject();

    virtual void setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) = 0;

protected:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 direction;
    bool remove{false};

};
