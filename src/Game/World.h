#pragma once

#include <vector>

#include "../Interface/ControlState.h"
#include "WorldState.h"
#include "Objects/Player.h"
#include "Objects/Bullet.h"


class World {
public:
    explicit World();
    void update(const ControlState& controlState, double deltaTime);
    Player getPlayer() const;
    std::vector<Bullet> getBullets() const;

private:
    WorldState worldState;
    Player player;
    std::vector<Bullet> bullets;
};
