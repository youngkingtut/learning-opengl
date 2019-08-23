#include <iostream>
#include "Enemy.h"
#include "../../Utils/Constants.h"


Enemy::Enemy(const glm::vec2& position) :
WorldObject(position, glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f)){}

void Enemy::setNextPosition(const ControlState &controlState, const GameState &worldState, const float &deltaTime) {
    glm::vec2 velocity = ENEMY_MAX_VELOCITY * (glm::normalize(glm::vec2(worldState.playerX - position[0], worldState.playerY - position[1])));
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];
}

void Enemy::bulletCollision(Bullet &bullet) {
    float distance = glm::distance(position, bullet.getPosition());

    if(distance <= ENEMY_RADIUS + BULLET_RADIUS) {
        remove = true;
        bullet.removeObject();
    }
}
