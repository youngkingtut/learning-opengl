#pragma once

#include "../../Interface/ControlState.h"
#include "WorldObject.h"


class Bullet : public WorldObject {
public:
    Bullet(const glm::vec2 &position, const glm::vec2 &velocity);
    void setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) override;
};
