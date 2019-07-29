#include "World.h"

#include <iostream>
#include "Constants.h"


World::World(float width, float height):
    width(width),
    height(height),
    lower_x(-width/2),
    lower_y(-height/2),
    upper_x(width/2),
    upper_y(height/2),
    player(){}

void World::update(ControlState controlState, double deltaTime) {
    // Update player position
    vmath::vec2 pos = player.getNextPosition(controlState, deltaTime);
    player.setPosition(BoundaryCheck(pos));
}

Player World::getPlayer() const {
    return player;
}

vmath::vec2 World::BoundaryCheck(vmath::vec2 position) {
    // todo take in to account object geometry
    if(position[0] > upper_x) {
        position[0] = upper_x;
    } else if (position[0] < lower_x) {
        position[0] = lower_x;
    }

    if(position[1] > upper_y) {
        position[1] = upper_y;
    } else if (position[1] < lower_y) {
        position[1] = lower_y;
    }

    return position;
}
