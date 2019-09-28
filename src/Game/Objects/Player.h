#pragma once

#include <vector>
#include "../../Interface/ControlState.h"
#include "WorldObject.h"
#include "Bullet.h"
#include "ChaserEnemy.h"


class Player: public WorldObject {
public:
    Player(const glm::vec2 &position, const glm::vec2 &velocity, const glm::vec2 &direction);
    void setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) override;
    void generateBullet(const ControlState& controlState, const float& deltaTime, std::vector<Bullet>& bullets);
    bool enemyCollision(const ChaserEnemy &enemy);

private:
    static float updateVelocity(float velocity, float targetVelocity, double deltaTime);
    void updateXVelocity(float targetVelocity, double deltaTime);
    void updateYVelocity(float targetVelocity, double deltaTime);

    float coolDown{0};
};
