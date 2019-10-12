#pragma once

#include "WorldObject.h"
#include "Bullet.h"


class ChaserEnemy : public WorldObject {
public:
    const static int value = 10;
    explicit ChaserEnemy(const glm::vec2 &position);
    void setNextPosition(const ControlState& controlState, const WorldState& worldState, const double& deltaTime) override;
    float getRadius() const override;
};
