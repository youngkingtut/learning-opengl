#pragma once

#include <vector>
#include "../../Interface/GameControlState.h"
#include "WorldObject.h"
#include "Bullet.h"
#include "ChaserEnemy.h"


class Player: public WorldObject {
public:
    Player() {};
    Player(const glm::vec2 &position, const glm::vec2 &velocity, const glm::vec2 &direction);
    void setNextPosition(const GameControlState& controlState, const WorldState& worldState, const double& deltaTime) override;
    void generateBullet(const GameControlState& controlState, const double& deltaTime, std::vector<Bullet>& bullets);
    float getRadius() const override;

private:
    static float updateVelocity(float velocity, float targetVelocity, double deltaTime);
    void updateXVelocity(float targetVelocity, double deltaTime);
    void updateYVelocity(float targetVelocity, double deltaTime);

    float coolDown{0};
};
