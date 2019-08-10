#include "World.h"

#include <iostream>
#include "../Utils/Constants.h"


World::World() :
bullets(),
player(vmath::vec2(PLAYER_SIZE_WIDTH, PLAYER_SIZE_HEIGHT), vmath::vec2(0, 0), vmath::vec2(0, 0), 0),
worldState{}
{
    worldState.worldLowerX = -WORLD_SIZE_WIDTH;
    worldState.worldLowerY = -WORLD_SIZE_HEIGHT;
    worldState.worldUpperX = WORLD_SIZE_WIDTH;
    worldState.worldUpperY = WORLD_SIZE_HEIGHT;
}

Player World::getPlayer() const {
    return player;
}

std::vector<Bullet> World::getBullets() const {
    return bullets;
}

void World::update(const ControlState& controlState, double deltaTime) {
    // Update player position and generate bullets
    player.setNextPosition(controlState, worldState, deltaTime);
    player.generateBullet(controlState, deltaTime, bullets);


    // Get next bullet position and remove out of bounds bullets
    for(auto & bullet : bullets) {
        bullet.setNextPosition(controlState, worldState, deltaTime);
    }
    auto new_end = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){return b.shouldRemove();});
    bullets.erase(new_end, bullets.end());
}
