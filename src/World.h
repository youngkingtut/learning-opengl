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
    float width;
    float height;

    Position BoundaryCheck(Position pos);
};
