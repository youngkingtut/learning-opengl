#pragma once

#include <vector>

#include "../Interface/ControlState.h"
#include "GameState.h"
#include "Objects/Player.h"
#include "Objects/Bullet.h"
#include "Objects/Enemy.h"


class World {
public:
    explicit World(GameState &state);

    void update(const ControlState& controlState, double deltaTime);
    Player getPlayer() const;
    std::vector<Bullet> getBullets() const;
    std::vector<Enemy> getEnemies() const;
    GameState getState() const;

private:
    GameState &gameState;
    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    double enemyCoolDown{0.0F};
    double deathCoolDown{0.0F};
    bool playerAlive{true};

    void removeObjects();
    void markAllObjectsForRemoval();
    void updateScore(int value);
    void updatePlayer(const ControlState& controlState, double deltaTime);
    void updateEnemies(const ControlState& controlState, double deltaTime);
    void updateBullets(const ControlState& controlState, double deltaTime);

    void playerDied();
};
