#include "World.h"

#include <algorithm>
#include <iostream>

#include "../Utils/Random.h"


World::World() :
        bullets(),
        moverEnemies(){
    worldState.worldLowerX = -WORLD_SIZE_WIDTH;
    worldState.worldLowerY = -WORLD_SIZE_HEIGHT;
    worldState.worldUpperX = WORLD_SIZE_WIDTH;
    worldState.worldUpperY = WORLD_SIZE_HEIGHT;
    worldState.playerX = 0.0F;
    worldState.playerY = 0.0F;
    worldState.score = 0;
    worldState.multiplier = 1;
    worldState.lives = 3;
    player = Player(glm::vec2(worldState.playerX, worldState.playerY), glm::vec2(0, 0), glm::vec2(0, 1));
}

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

WorldState World::getState() const {
    return worldState;
}

GameState World::update(const ControlState& controlState, double deltaTime) {
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

    if(worldState.lives > 0) {
        spawnEnemies(controlState, deltaTime);
        return GameState::GAME_RUNNING;
    } else {
        return GameState::GAME_OVER;
    }
}

void World::updateScore(int value) {
    worldState.score += worldState.multiplier * value;
}

void World::markAllObjectsForRemoval() {
    for(auto& enemy : moverEnemies) {
        enemy.removeObject();
    }
    for(auto& enemy : simpleEnemies) {
        enemy.removeObject();
    }
    for(auto& bullet : bullets) {
        bullet.removeObject();
    }
}

void World::removeObjects() {
    // Remove Bullets
    auto new_end = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){return b.shouldRemove();});
    bullets.erase(new_end, bullets.end());

    // Remove Enemies, update score
    auto moverEnemyHead = moverEnemies.begin();
    for(auto enemy = moverEnemies.begin(); enemy != moverEnemies.end(); enemy++) {
        if(enemy->shouldRemove()) {
            if(playerAlive) {
                updateScore(ChaserEnemy::value);
            }
            std::iter_swap(moverEnemyHead, enemy);
            moverEnemyHead++;
        }
    }
    moverEnemies.erase(moverEnemies.begin(), moverEnemyHead);

    auto simpleEnemyHead = simpleEnemies.begin();
    for(auto enemy = simpleEnemies.begin(); enemy != simpleEnemies.end(); enemy++) {
        if(enemy->shouldRemove()) {
            if(playerAlive) {
                updateScore(SimpleEnemy::value);
            }
            std::iter_swap(simpleEnemyHead, enemy);
            simpleEnemyHead++;
        }
    }
    simpleEnemies.erase(simpleEnemies.begin(), simpleEnemyHead);
}

void World::updatePlayer(const ControlState& controlState, const double& deltaTime) {
    player.setNextPosition(controlState, worldState, deltaTime);
    glm::vec2 playerPosition = player.getPosition();
    worldState.playerX = playerPosition[0];
    worldState.playerY = playerPosition[1];
    player.generateBullet(controlState, deltaTime, bullets);
}

void World::updateEnemies(const ControlState& controlState, const double& deltaTime) {
    for(ChaserEnemy &enemy: moverEnemies) {
        enemy.setNextPosition(controlState, worldState, deltaTime);
        if(player.collision(enemy)) {
            playerDied();
        }
    }
    for(SimpleEnemy& enemy: simpleEnemies) {
        enemy.setNextPosition(controlState, worldState, deltaTime);
        if(player.collision(enemy)) {
            playerDied();
        }
    }
}

void World::updateBullets(const ControlState& controlState, const double& deltaTime) {
    for(auto &bullet : bullets) {
        bullet.setNextPosition(controlState, worldState, deltaTime);
        for(auto &enemy: moverEnemies) {
            if(!bullet.shouldRemove()) {
                if(enemy.collision(bullet)) {
                    enemy.removeObject();
                    bullet.removeObject();
                }
            }
        }
        for(auto& enemy: simpleEnemies) {
            if(!bullet.shouldRemove()) {
                if(enemy.collision(bullet)) {
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
        worldState.lives -= 1;
    }
}

void World::spawnEnemies(const ControlState& controlState, const double &deltaTime) {
    if(SPAWN_ENEMIES && playerAlive) {
        enemyCoolDown += deltaTime;


        // Random spawn avoiding some player safe zone

        if (enemyCoolDown > WORLD_ENEMY_COOL_DOWN) {
            glm::vec2 spawnPoint = getRandomPoint();
            if (glm::distance(spawnPoint, player.getPosition()) > RANDOM_SPAWN_PLAYER_SAFE_ZONE_RADIUS) {
                enemyCoolDown = 0.0F;
                switch((Random::getRandomInt(0, 1))) {
                    case 0:
                        simpleEnemies.emplace_back(SimpleEnemy(spawnPoint));
                        break;
                    case 1:
                        moverEnemies.emplace_back(ChaserEnemy(spawnPoint));
                        break;
                    default:
                        break;
                }
            }
        }

//    // Corner flood Pattern
//    if(SPAWN_ENEMIES && playerAlive) {
//        // Generate Enemies
//        enemyCoolDown += deltaTime;
//        if (enemyCoolDown > WORLD_ENEMY_COOL_DOWN) {
//            enemyCoolDown = 0.0F;
//            float upperX = worldState.worldUpperX - CHASER_ENEMY_RADIUS;
//            float lowerX = worldState.worldLowerX + CHASER_ENEMY_RADIUS;
//
//            float upperY = worldState.worldUpperY - CHASER_ENEMY_RADIUS;
//            float lowerY = worldState.worldLowerY + CHASER_ENEMY_RADIUS;
//
//            moverEnemies.emplace_back(ChaserEnemy(glm::vec2(upperX, upperY)));
//            moverEnemies.emplace_back(ChaserEnemy(glm::vec2(upperX, lowerY)));
//            moverEnemies.emplace_back(ChaserEnemy(glm::vec2(lowerX, upperY)));
//            moverEnemies.emplace_back(ChaserEnemy(glm::vec2(lowerX, lowerY)));
//        }
//    }
    }
}

glm::vec2 World::getRandomPoint() {
    return glm::vec2(Random::getRandomFloat(-WORLD_SIZE_WIDTH, WORLD_SIZE_WIDTH),Random::getRandomFloat(-WORLD_SIZE_HEIGHT, WORLD_SIZE_HEIGHT));
}
