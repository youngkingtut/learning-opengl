#include "World.h"

#include <iostream>

double World::FPS_60 = 1.0f / 60.0f;

void World::initialize(ConfigStore config) {
    width = config.getWorldWidth();
    height = config.getWorldHeight();

    if(width < 1.0f) {
        width = 1.0f;
        std::cout << "World width must be at least 1.0f" << std::endl;
    }

    if(height < 1.0f) {
        height = 1.0f;
        std::cout << "World height must be at least 1.0f" << std::endl;
    }

    player.initialize(width / 2, height / 2, 0, 0, vmath::vec3(1.0f, 0.0f, 0.0f));
}

void World::updateFromInput(ControlState controlState, double deltaTime) {
    // If the fps drops below 60, use this factor to slow down world updates
    // to compensate and give the user a more smooth experience at the cost
    // of world slow down.
    double smoothnessFactor = 1.0f;

    if(deltaTime > FPS_60) {
        smoothnessFactor = deltaTime / FPS_60;
    }

    double upFactor = controlState.getUp() * smoothnessFactor;
    double downFactor = controlState.getDown() * smoothnessFactor;
    double leftFactor = controlState.getLeft() * smoothnessFactor;
    double rightFactor = controlState.getRight() * smoothnessFactor;

    if(upFactor > 0.0f) {
        player.updateYVelocity(VelocityUpdate::INCREASE, upFactor);
    } else {
        player.updateYVelocity(VelocityUpdate::DECREASE_TO_ZERO, 0.3);
    }

    if(downFactor > 0.0f) {
        player.updateYVelocity(VelocityUpdate::DECREASE, downFactor);
    } else {
        player.updateYVelocity(VelocityUpdate::INCREASE_TO_ZERO, 0.3);
    }

    if(leftFactor > 0.0f) {
        player.updateXVelocity(VelocityUpdate::DECREASE, leftFactor);
    } else {
        player.updateXVelocity(VelocityUpdate::INCREASE_TO_ZERO, 2.0);
    }

    if(rightFactor > 0.0f) {
        player.updateXVelocity(VelocityUpdate::INCREASE, rightFactor);
    } else {
        player.updateXVelocity(VelocityUpdate::DECREASE_TO_ZERO, 2.0);
    }

    player.updatePosition(FPS_60 * smoothnessFactor);

    std::cout << "Player x: " << player.getXPosition() << " | Player y: " << player.getYPosition() << std::endl;
}
