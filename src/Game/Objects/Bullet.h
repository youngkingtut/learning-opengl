#pragma once

#include <vmath.h>

#include "../../Interface/ControlState.h"
#include "WorldObject.h"


class Bullet : public WorldObject {
public:
    Bullet(const vmath::vec2 &size, const vmath::vec2 &position, const vmath::vec2 &velocity, float angle);
    vmath::vec2 setNextPosition(const ControlState &controlState, double deltaTime);
    bool shouldRemove() const;
    void setRemove(bool r);

private:
    bool remove;
};
