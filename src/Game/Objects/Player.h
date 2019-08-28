#pragma once

#include <vector>
#include "../../Interface/ControlState.h"
#include "WorldObject.h"
#include "Bullet.h"
#include "Enemy.h"


enum VelocityUpdate {
    INCREASE,
    TO_ZERO
};

class Player: public WorldObject {
public:
    Player(const glm::vec2 &position, const glm::vec2 &velocity, const glm::vec2 &direction);
    void setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) override;
    void generateBullet(const ControlState& controlState, const float& deltaTime, std::vector<Bullet>& bullets);
    bool enemyCollision(const Enemy &enemy);

private:
    float updateVelocity(float velocity, VelocityUpdate vUpdate, double deltaTime);
    void updateXVelocity(VelocityUpdate vUpdate, double deltaTime);
    void updateYVelocity(VelocityUpdate vUpdate, double deltaTime);

    float coolDown{0};
};
