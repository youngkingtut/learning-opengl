#pragma once

#include <vmath.h>
#include "../../Interface/ControlState.h"
#include "../WorldState.h"


class WorldObject {
public:
    WorldObject(vmath::vec2  size, vmath::vec2  position, vmath::vec2  velocity, const float &angle);
    bool shouldRemove() const;
    vmath::vec2 getPosition() const;
    vmath::vec2 getSize() const;
    float getAngle() const;
    void removeObject();

    virtual void setNextPosition(const ControlState& controlState, const WorldState& worldState, const float& deltaTime) = 0;

protected:
    vmath::vec2 size;
    vmath::vec2 position;
    vmath::vec2 velocity;
    float angle{0};
    bool remove{false};

    static float calculateAngle(vmath::vec2& dir);
};
