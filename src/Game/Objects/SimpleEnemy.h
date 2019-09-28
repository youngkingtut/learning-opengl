#pragma once

#include "WorldObject.h"
#include "Bullet.h"


class SimpleEnemy : public WorldObject {
public:
    const static int value = 10;
    explicit SimpleEnemy(const glm::vec2 &position);
    void setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) override;
    bool bulletCollision(Bullet &bullet);
};

