#include "World.h"

#include <iostream>


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

    player.initialize(width / 2, height / 2, 0);
}

void World::updateFromInput(ControlState controlState) {

}
