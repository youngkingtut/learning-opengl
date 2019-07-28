#pragma once

#include "ConfigStore.h"
#include "Player.h"
#include "ControlState.h"

class World {
public:
    World() = default;
    World(float width, float height);
    void initialize(ConfigStore config);
    void updateFromInput(ControlState controlState, double deltaTime);
    Player getPlayer() const;

private:
    Position BoundaryCheck(Position pos);

    static double FPS_60;
    Player player;
    float width;
    float height;
};
