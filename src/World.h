#pragma once

#include "ConfigStore.h"
#include "Player.h"
#include "ControlState.h"

class World {
public:
    World(float width, float height);
    void update(ControlState controlState, double deltaTime);
    Player getPlayer() const;

private:
    Player player;
    float lower_x;
    float lower_y;
    float upper_x;
    float upper_y;
    float width;
    float height;

    vmath::vec2 BoundaryCheck(vmath::vec2 position);
};
