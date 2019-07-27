#pragma once

#include "ConfigStore.h"
#include "Player.h"
#include "ControlState.h"

class World {
public:
    void initialize(ConfigStore config);
    void updateFromInput(ControlState controlState);

private:
    Player player;
    float width;
    float height;
};
