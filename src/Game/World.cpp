#include "World.h"

#include <iostream>
#include "../Utils/Constants.h"


World::World() :
bullets(),
enemies(),
player(vmath::vec2(PLAYER_SIZE_WIDTH, PLAYER_SIZE_HEIGHT), vmath::vec2(0, 0), vmath::vec2(0, 0), 0),
worldState{}
{
    worldState.worldLowerX = -WORLD_SIZE_WIDTH;
    worldState.worldLowerY = -WORLD_SIZE_HEIGHT;
    worldState.worldUpperX = WORLD_SIZE_WIDTH;
    worldState.worldUpperY = WORLD_SIZE_HEIGHT;
    worldState.playerX = 0.0f;
    worldState.playerY = 0.0f;
    enemies.emplace_back(Enemy(vmath::vec2(10.0f, 10.0f), vmath::vec2(100.0f, 100.0f)));
    enemies.emplace_back(Enemy(vmath::vec2(10.0f, 10.0f), vmath::vec2(-100.0f, -100.0f)));
}

Player World::getPlayer() const {
    return player;
}

std::vector<Bullet> World::getBullets() const {
    return bullets;
}

std::vector<Enemy> World::getEnemies() const {
    return enemies;
}

void World::update(const ControlState& controlState, double deltaTime) {
    // Update player position and generate bullets
    player.setNextPosition(controlState, worldState, deltaTime);
    player.generateBullet(controlState, deltaTime, bullets);
    vmath::vec2 playerPosition = player.getPosition();
    worldState.playerX = playerPosition[0];
    worldState.playerY = playerPosition[1];

    // Get next bullet position and remove out of bounds bullets
    for(auto & bullet : bullets) {
        bullet.setNextPosition(controlState, worldState, deltaTime);
    }
    auto new_end = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){return b.shouldRemove();});
    bullets.erase(new_end, bullets.end());


    // Handle enemies
    for(auto & enemy: enemies) {
        enemy.setNextPosition(controlState, worldState, deltaTime);
    }
    auto enemyEnd = std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e){return e.shouldRemove();});
    enemies.erase(enemyEnd, enemies.end());


}
