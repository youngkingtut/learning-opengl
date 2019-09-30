#pragma once

#include <vector>
#include <random>

#include "../Utils/Constants.h"
#include "../Interface/ControlState.h"
#include "GameState.h"
#include "Objects/Player.h"
#include "Objects/Bullet.h"
#include "Objects/ChaserEnemy.h"
#include "Objects/SimpleEnemy.h"


class World {
public:
    explicit World(GameState &state);

    void update(const ControlState& controlState, double deltaTime);
    Player getPlayer() const;
    std::vector<Bullet> getBullets() const;
    std::vector<ChaserEnemy> getMoverEnemies() const;
    std::vector<SimpleEnemy> getSimpleEnemies() const;
    GameState getState() const;

private:
    GameState &gameState;
    Player player;
    std::vector<Bullet> bullets;
    std::vector<ChaserEnemy> moverEnemies;
    std::vector<SimpleEnemy> simpleEnemies;

    std::random_device rd;
    std::mt19937 randomGenerator{rd()};
    std::uniform_real_distribution<> worldHeightDistribution{-WORLD_SIZE_HEIGHT, WORLD_SIZE_HEIGHT};
    std::uniform_real_distribution<> worldWidthDistribution{- WORLD_SIZE_WIDTH, WORLD_SIZE_WIDTH};
    std::uniform_int_distribution<> enemyDistribution{0, 2};

    double enemyCoolDown{0.0F};
    double deathCoolDown{0.0F};
    bool playerAlive{true};

    void removeObjects();
    void markAllObjectsForRemoval();
    void updateScore(int value);
    void updatePlayer(const ControlState& controlState, const double& deltaTime);
    void updateEnemies(const ControlState& controlState, const double& deltaTime);
    void updateBullets(const ControlState& controlState, const double& deltaTime);

    void spawnEnemies(const ControlState& controlState, const double& deltaTime);

    void playerDied();

    glm::vec2 getRandomPoint();
};
