#pragma once

#include "WorldObject.h"
#include "Bullet.h"


class SimpleEnemy : public WorldObject {
public:
    const static int value = 5;
    explicit SimpleEnemy(const glm::vec2 &position);
    void setNextPosition(const ControlState& controlState, const WorldState& worldState, const double& deltaTime) override;
    float getRadius() const override;

private:
    float rotationSpeed;
};

