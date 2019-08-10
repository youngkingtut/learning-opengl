#pragma once

#include <vmath.h>

#include "../../Interface/ControlState.h"
#include "WorldObject.h"


class Bullet : public WorldObject {
public:
    Bullet(const vmath::vec2 &size, const vmath::vec2 &position, const vmath::vec2 &velocity, float angle);
    void setNextPosition(const ControlState& controlState, const WorldState& worldState, const float& deltaTime) override;
};
