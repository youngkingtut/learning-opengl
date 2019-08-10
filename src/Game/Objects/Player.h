#pragma once

#include <vector>
#include <vmath.h>
#include "../../Interface/ControlState.h"
#include "WorldObject.h"
#include "Bullet.h"


enum VelocityUpdate {
    INCREASE,
    TO_ZERO
};

class Player: public WorldObject {
public:
    explicit Player(vmath::vec2 size, vmath::vec2 position, vmath::vec2 velocity, float angle);
    void setNextPosition(const ControlState& controlState, const WorldState& worldState, const float& deltaTime) override;
    void generateBullet(const ControlState& controlState, const float& deltaTime, std::vector<Bullet>& bullets);

private:
    float updateVelocity(float velocity, VelocityUpdate vUpdate, double deltaTime);
    void updateXVelocity(VelocityUpdate vUpdate, double deltaTime);
    void updateYVelocity(VelocityUpdate vUpdate, double deltaTime);

    float coolDown;
};
