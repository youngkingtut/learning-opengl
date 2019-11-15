#pragma once

#include "../../Interface/GameControlState.h"
#include "WorldObject.h"


class Bullet : public WorldObject {
public:
    Bullet(const glm::vec2 &position, const glm::vec2 &velocity, const glm::vec2 &direction);
    void setNextPosition(const GameControlState& controlState, const WorldState& worldState, const double& deltaTime) override;
    float getRadius() const override;
};
