#include "World.h"

#include <iostream>

double World::FPS_60 = 1.0f / 60.0f;

void World::initialize(ConfigStore config) {
    width = config.getWorldWidth();
    height = config.getWorldHeight();

    player.initialize(width / 2, height / 2, 0, 0, vmath::vec3(1.0f, 0.0f, 0.0f));
}

void World::updateFromInput(ControlState controlState, double deltaTime) {
    double smoothnessFactor = deltaTime / FPS_60;

    double upFactor = controlState.getUp();
    double downFactor = controlState.getDown();
    double leftFactor = controlState.getLeft();
    double rightFactor = controlState.getRight();

    if(upFactor > 0.0f) {
        player.updateYVelocity(VelocityUpdate::INCREASE, upFactor * smoothnessFactor);
    }

    if(downFactor > 0.0f) {
        player.updateYVelocity(VelocityUpdate::DECREASE, downFactor * smoothnessFactor);
    }

    if(leftFactor > 0.0f) {
        player.updateXVelocity(VelocityUpdate::DECREASE, leftFactor * smoothnessFactor);
    }

    if(rightFactor > 0.0f) {
        player.updateXVelocity(VelocityUpdate::INCREASE, rightFactor * smoothnessFactor);
    }

    if(upFactor == 0.0f && downFactor == 0.0f) {
        player.updateYVelocity(VelocityUpdate::TO_ZERO, smoothnessFactor);
    }

    if(leftFactor == 0.0f && rightFactor == 0.0f) {
        player.updateXVelocity(VelocityUpdate::TO_ZERO, smoothnessFactor);
    }

    Position pos = player.getNextPosition(deltaTime);

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

World::World(float width, float height) {
    this->width = width;
    this->height = height;
}
