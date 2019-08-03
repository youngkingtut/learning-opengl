#pragma once

#include "../Interface/ControlState.h"
#include "../Utils/ConfigStore.h"
#include "Player.h"

class World {
public:
    World();
    void update(const ControlState& controlState, double deltaTime);
    Player getPlayer() const;

    vmath::vec2 getSize() const;

private:
    Player player;
    vmath::vec2 size;
    float lower_x;
    float lower_y;
    float upper_x;
    float upper_y;

    vmath::vec2 BoundaryCheck(vmath::vec2 position, vmath::vec2 size);
};
