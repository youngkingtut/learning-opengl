#include "World.h"

#include <random>
#include <iostream>
#include "../Utils/Constants.h"


World::World(GameState &state) :
    bullets(),
    enemies(),
    gameState(state),
    player(glm::vec2(PLAYER_SIZE_WIDTH, PLAYER_SIZE_HEIGHT), glm::vec2(state.playerX, state.playerY), glm::vec2(0, 0), 0){}

Player World::getPlayer() const {
    return player;
}

std::vector<Bullet> World::getBullets() const {
    return bullets;
}

std::vector<Enemy> World::getEnemies() const {
    return enemies;
}

GameState World::getState() const {
    return gameState;
}

void World::update(const ControlState& controlState, double deltaTime) {
    // Update player position and generate bullets
    player.setNextPosition(controlState, gameState, deltaTime);
    player.generateBullet(controlState, deltaTime, bullets);
    glm::vec2 playerPosition = player.getPosition();
    gameState.playerX = playerPosition[0];
    gameState.playerY = playerPosition[1];

    // Bullets
    for(auto & bullet : bullets) {
        bullet.setNextPosition(controlState, gameState, deltaTime);
    }

    // Enemies
    for(auto & enemy: enemies) {
        enemy.setNextPosition(controlState, gameState, deltaTime);
    }

    // Bullet collision with enemy
    for(auto & bullet : bullets) {
        for(auto & enemy: enemies) {
            enemy.bulletCollision(bullet);
        }
    }

    // Remove Bullets
    auto new_end = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){return b.shouldRemove();});
    bullets.erase(new_end, bullets.end());

    removeEnemies();

    // Generate Enemies
    coolDown += deltaTime;
    if(coolDown > WORLD_ENEMY_COOL_DOWN) {
        coolDown = 0.0f;
        float enemyX = std::rand() % (int) gameState.worldUpperX;
        float enemyY = std::rand() % (int) gameState.worldUpperY;
        if (std::rand() % 2 > 0) {
            enemyX = -enemyX;
        }
        if (std::rand() % 2 > 0) {
            enemyY = -enemyY;
        }
        enemies.emplace_back(Enemy(glm::vec2(10.0f, 10.0f), glm::vec2(enemyX, enemyY)));
    }
}

void World::removeEnemies() {
    auto head = enemies.begin();
    for(auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
        if(enemy->shouldRemove()) {
            updateScore(Enemy::value);
            std::iter_swap(head, enemy);
            head++;
        }
    }
    enemies.erase(enemies.begin(), head);
}

void World::updateScore(int value) {
    gameState.score += gameState.multiplier * value;
}
