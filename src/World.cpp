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
    player(0, 0, 0, 0, vmath::vec2(-1.0f, 0.0f)){
}

void World::update(ControlState controlState, double deltaTime) {
    // Update player position
    Position pos = player.getNextPosition(controlState, deltaTime);
    player.setPosition(BoundaryCheck(pos));
}

Player World::getPlayer() const {
    return player;
}

Position World::BoundaryCheck(Position pos) {
    if(pos.x > upper_x) {
        pos.x = upper_x;
    } else if (pos.x < lower_x) {
        pos.x = lower_x;
    }

    if(pos.y > upper_y) {
        pos.y = upper_y;
    } else if (pos.y < lower_y) {
        pos.y = lower_y;
    }

    return pos;
}
