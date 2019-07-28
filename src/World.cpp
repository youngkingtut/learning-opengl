#include "World.h"

#include <iostream>
#include "Constants.h"


World::World(float width, float height):
    width(width),
    height(height),
    player(width / 2, height / 2, 0, 0, vmath::vec3(1.0f, 0.0f, 0.0f)){}

void World::update(ControlState controlState, double deltaTime) {
    // Update player position
    Position pos = player.getNextPosition(controlState, deltaTime);
    player.updatePosition(BoundaryCheck(pos));
}

Player World::getPlayer() const {
    return player;
}

Position World::BoundaryCheck(Position pos) {
    if(pos.x > width) {
        pos.x = width;
    } else if (pos.x < 0) {
        pos.x = 0;
    }

    if(pos.y > height) {
        pos.y = height;
    } else if (pos.y < 0) {
        pos.y = 0;
    }

    return pos;
}
