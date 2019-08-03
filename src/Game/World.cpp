#include "World.h"

#include <iostream>
#include "../Utils/Constants.h"


World::World() :
player(vmath::vec2(20, 20)),
size(vmath::vec2(400, 300))
{
    lower_x = -size[0];
    lower_y = -size[1];
    upper_x = size[0];
    upper_y = size[1];
}

void World::update(const ControlState& controlState, double deltaTime) {
    // Update player position
    vmath::vec2 pos = player.setNextPosition(controlState, deltaTime);

    player.setPosition(BoundaryCheck(pos, player.getSize()));
}

vmath::vec2 World::BoundaryCheck(vmath::vec2 position, vmath::vec2 s) {
    // todo take in to account object geometry
    if(position[0] + s[0] > upper_x) {
        position[0] = upper_x - s[0];
    } else if (position[0] - s[0] < lower_x) {
        position[0] = lower_x + s[0];
    }

    if(position[1] + s[1] > upper_y) {
        position[1] = upper_y - s[1];
    } else if (position[1] - s[1] < lower_y) {
        position[1] = lower_y + s[1];
    }

    return position;
}

vmath::vec2 World::getSize() const {
    return size;
}

Player World::getPlayer() const {
    return player;
}
