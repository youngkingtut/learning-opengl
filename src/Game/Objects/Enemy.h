#pragma once

#include "WorldObject.h"
#include "Bullet.h"


class Enemy : public WorldObject {
public:
    const static int value = 10;
    explicit Enemy(const glm::vec2 &position);
    void setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) override;
    bool bulletCollision(Bullet &bullet);
};
