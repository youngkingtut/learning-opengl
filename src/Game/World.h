#pragma once

#include <vector>

#include "../Interface/ControlState.h"
#include "../Utils/ConfigStore.h"
#include "Objects/Player.h"
#include "Objects/Bullet.h"

class World {
public:
    explicit World(ConfigStore configStore);
    void update(const ControlState& controlState, double deltaTime);
    Player getPlayer() const;
    std::vector<Bullet> getBullets() const;

private:
    ConfigStore config;
    Player player;
    float cooldown;
    float lower_x;
    float lower_y;
    float upper_x;
    float upper_y;
    std::vector<Bullet> bullets;

    bool outOfBounds(vmath::vec2 position, vmath::vec2 size);
    vmath::vec2 BoundaryCheck(vmath::vec2 position, vmath::vec2 size);
};
