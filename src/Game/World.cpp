#include "World.h"

#include <random>
#include <algorithm>
#include <iostream>
#include "../Utils/Constants.h"


World::World(GameState &state) :
        bullets(),
        moverEnemies(),
        gameState(state),
        player(glm::vec2(state.playerX, state.playerY), glm::vec2(0, 0), glm::vec2(0, 1)){}

Player World::getPlayer() const {
    return player;
}

std::vector<Bullet> World::getBullets() const {
    return bullets;
}

std::vector<ChaserEnemy> World::getMoverEnemies() const {
    return moverEnemies;
}

std::vector<SimpleEnemy> World::getSimpleEnemies() const {
    return simpleEnemies;
}

GameState World::getState() const {
    return gameState;
}

void World::update(const ControlState& controlState, double deltaTime) {
    if(playerAlive) {
        updatePlayer(controlState, deltaTime);
        updateEnemies(controlState, deltaTime);
        updateBullets(controlState, deltaTime);
    }

    if(!playerAlive) {
        markAllObjectsForRemoval();
        deathCoolDown += deltaTime;

        if(deathCoolDown > WORLD_DEATH_COOL_DOWN) {
            deathCoolDown = 0.0F;
            playerAlive = true;
        }
    }

    removeObjects();

    if(SPAWN_ENEMIES && playerAlive) {
        // Generate Enemies
        enemyCoolDown += deltaTime;
        if (enemyCoolDown > WORLD_ENEMY_COOL_DOWN) {
            enemyCoolDown = 0.0F;
            float upperX = gameState.worldUpperX - ENEMY_RADIUS;
            float lowerX = gameState.worldLowerX + ENEMY_RADIUS;

            float upperY = gameState.worldUpperY - ENEMY_RADIUS;
            float lowerY = gameState.worldLowerY + ENEMY_RADIUS;

            moverEnemies.emplace_back(ChaserEnemy(glm::vec2(upperX, upperY)));
            moverEnemies.emplace_back(ChaserEnemy(glm::vec2(upperX, lowerY)));
            moverEnemies.emplace_back(ChaserEnemy(glm::vec2(lowerX, upperY)));
            moverEnemies.emplace_back(ChaserEnemy(glm::vec2(lowerX, lowerY)));
        }
    }
}

void World::updateScore(int value) {
    gameState.score += gameState.multiplier * value;
}

void World::markAllObjectsForRemoval() {
    for(auto & enemy : moverEnemies) {
        enemy.removeObject();
    }
    for(auto & bullet : bullets) {
        bullet.removeObject();
    }
}

void World::removeObjects() {
    // Remove Bullets
    auto new_end = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){return b.shouldRemove();});
    bullets.erase(new_end, bullets.end());

    // Remove Enemies, update score
    auto head = moverEnemies.begin();
    for(auto enemy = moverEnemies.begin(); enemy != moverEnemies.end(); enemy++) {
        if(enemy->shouldRemove()) {
            if(playerAlive) {
                updateScore(ChaserEnemy::value);
            }
            std::iter_swap(head, enemy);
            head++;
        }
    }
    moverEnemies.erase(moverEnemies.begin(), head);
}

void World::updatePlayer(const ControlState& controlState, double deltaTime) {
    player.setNextPosition(controlState, gameState, deltaTime);
    glm::vec2 playerPosition = player.getPosition();
    gameState.playerX = playerPosition[0];
    gameState.playerY = playerPosition[1];
    player.generateBullet(controlState, deltaTime, bullets);
}

void World::updateEnemies(const ControlState& controlState, double deltaTime) {
    for(ChaserEnemy &enemy: moverEnemies) {
        enemy.setNextPosition(controlState, gameState, deltaTime);
        if(player.enemyCollision(enemy)) {
            playerDied();
        }
    }
}

void World::updateBullets(const ControlState& controlState, double deltaTime) {
    for(auto &bullet : bullets) {
        bullet.setNextPosition(controlState, gameState, deltaTime);
        for(auto &enemy: moverEnemies) {
            if(!bullet.shouldRemove()) {
                if(enemy.bulletCollision(bullet)) {
                    enemy.removeObject();
                    bullet.removeObject();
                }
            }
        }
    }
}

void World::playerDied() {
    if(playerAlive) {
        player.zeroVelocity();
        playerAlive = false;
        gameState.lives -= 1;
    }
}
