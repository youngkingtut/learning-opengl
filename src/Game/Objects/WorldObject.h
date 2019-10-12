#pragma once

#include "../../Interface/ControlState.h"
#include "../WorldState.h"


class WorldObject {
public:
    WorldObject();
    WorldObject(const glm::vec2 &position, const glm::vec2 &velocity, const glm::vec2 &direction);
    bool shouldRemove() const;
    float getAngle() const;
    glm::vec2 getPosition() const;
    void removeObject();
    bool collision(const WorldObject &object);
    void zeroVelocity();

    virtual float getRadius() const = 0;
    virtual void setNextPosition(const ControlState& controlState, const WorldState& worldState, const double& deltaTime) = 0;

protected:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 direction;
    bool remove{false};
};
