#pragma once

#include "ConfigStore.h"
#include "Player.h"
#include "ControlState.h"

class World {
public:
    void initialize(ConfigStore config);
    void updateFromInput(ControlState controlState, double deltaTime);

private:
    static double FPS_60;
    Player player;
    float width;
    float height;
};
