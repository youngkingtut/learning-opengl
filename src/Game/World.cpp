#include "World.h"

#include <random>
#include "../Utils/Constants.h"


World::World() :
bullets(),
enemies(),
player(glm::vec2(PLAYER_SIZE_WIDTH, PLAYER_SIZE_HEIGHT), glm::vec2(0, 0), glm::vec2(0, 0), 0),
worldState{}
{
    worldState.worldLowerX = -WORLD_SIZE_WIDTH;
    worldState.worldLowerY = -WORLD_SIZE_HEIGHT;
    worldState.worldUpperX = WORLD_SIZE_WIDTH;
    worldState.worldUpperY = WORLD_SIZE_HEIGHT;
    worldState.playerX = 0.0f;
    worldState.playerY = 0.0f;
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
    glm::vec2 playerPosition = player.getPosition();
    worldState.playerX = playerPosition[0];
    worldState.playerY = playerPosition[1];

    // Bullets
    for(auto & bullet : bullets) {
        bullet.setNextPosition(controlState, worldState, deltaTime);
    }

    // Enemies
    for(auto & enemy: enemies) {
        enemy.setNextPosition(controlState, worldState, deltaTime);
    }

    // Bullet collision with enemy
    for(auto & bullet : bullets) {
        for(auto & enemy: enemies) {
            enemy.bulletCollision(bullet);
        }
    }

    // Remove any object marked as such
    auto new_end = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){return b.shouldRemove();});
    bullets.erase(new_end, bullets.end());
    auto enemyEnd = std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e){return e.shouldRemove();});
    enemies.erase(enemyEnd, enemies.end());


    // Generate Enemies
    coolDown += deltaTime;
    if(coolDown > WORLD_ENEMY_COOL_DOWN) {
        coolDown = 0.0f;
        float enemyX = std::rand() % (int) worldState.worldUpperX;
        float enemyY = std::rand() % (int) worldState.worldUpperY;
        if (std::rand() % 2 > 0) {
            enemyX = -enemyX;
        }
        if (std::rand() % 2 > 0) {
            enemyY = -enemyY;
        }
        enemies.emplace_back(Enemy(glm::vec2(10.0f, 10.0f), glm::vec2(enemyX, enemyY)));
    }
}
