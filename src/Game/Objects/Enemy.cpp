#include <utility>

#include "../../Utils/Constants.h"
#include "Enemy.h"

Enemy::Enemy(vmath::vec2 size, vmath::vec2 position) :
WorldObject(std::move(size), std::move(position), vmath::vec2(0.0f, 0.0f), 0){}

void Enemy::setNextPosition(const ControlState &controlState, const WorldState &worldState, const float &deltaTime) {
    vmath::vec2 velocity = ENEMY_MAX_VELOCITY * (vmath::normalize(vmath::vec2(worldState.playerX - position[0], worldState.playerY - position[1])));
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];
}
