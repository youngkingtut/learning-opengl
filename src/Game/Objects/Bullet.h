#pragma once

#include "../../Interface/ControlState.h"
#include "WorldObject.h"


class Bullet : public WorldObject {
public:
    Bullet(const glm::vec2 &size, const glm::vec2 &position, const glm::vec2 &velocity, float angle);
    void setNextPosition(const ControlState& controlState, const WorldState& worldState, const float& deltaTime) override;
};
