#pragma once

#include <vmath.h>
#include "../../Interface/ControlState.h"
#include "WorldObject.h"


enum VelocityUpdate {
    INCREASE,
    TO_ZERO
};

class Player: public WorldObject {
public:
    explicit Player(vmath::vec2 size, vmath::vec2 position, vmath::vec2 velocity, float angle);
    vmath::vec2 setNextPosition(const ControlState &controlState, double deltaTime);

private:
    static float updateVelocity(float velocity, VelocityUpdate vUpdate, double deltaTime);
    void updateXVelocity(VelocityUpdate vUpdate, double deltaTime);
    void updateYVelocity(VelocityUpdate vUpdate, double deltaTime);
};
