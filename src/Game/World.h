#pragma once

#include <vector>

#include "../Utils/Constants.h"
#include "../Interface/GameControlState.h"
#include "WorldState.h"
#include "Objects/Player.h"
#include "Objects/Bullet.h"
#include "Objects/ChaserEnemy.h"
#include "Objects/SimpleEnemy.h"
#include "GameState.h"


class World {
public:
    explicit World();

    GameState update(const GameControlState& gameControlState, double deltaTime);
    Player getPlayer() const;
    std::vector<Bullet> getBullets() const;
    std::vector<ChaserEnemy> getMoverEnemies() const;
    std::vector<SimpleEnemy> getSimpleEnemies() const;
    WorldState getState() const;

    void reset();

private:
    WorldState worldState;
    Player player;
    std::vector<Bullet> bullets;
    std::vector<ChaserEnemy> moverEnemies;
    std::vector<SimpleEnemy> simpleEnemies;

    double enemyCoolDown{0.0F};
    double deathCoolDown{0.0F};
    bool playerAlive{true};

    void removeObjects();
    void markAllObjectsForRemoval();
    void updateScore(int value);
    void updatePlayer(const GameControlState& controlState, const double& deltaTime);
    void updateEnemies(const GameControlState& controlState, const double& deltaTime);
    void updateBullets(const GameControlState& controlState, const double& deltaTime);

    void spawnEnemies(const GameControlState& controlState, const double& deltaTime);

    void playerDied();

    static glm::vec2 getRandomPoint() ;
};
