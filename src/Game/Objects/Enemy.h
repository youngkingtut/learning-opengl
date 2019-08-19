#pragma once

#include "WorldObject.h"
#include "Bullet.h"


class Enemy : public WorldObject {
public:
    Enemy(const glm::vec2& size, const glm::vec2& position);
    void setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) override;
    void bulletCollision(Bullet &bullet);
};
