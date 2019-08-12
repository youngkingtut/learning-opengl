#pragma once

#include "WorldObject.h"
#include "Bullet.h"


class Enemy : public WorldObject {
public:
    Enemy(vmath::vec2 size, vmath::vec2 position);
    void setNextPosition(const ControlState& controlState, const WorldState& worldState, const float& deltaTime) override;
    void bulletCollision(Bullet & bullet);
};
