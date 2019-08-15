#include "Enemy.h"
#include "../../Utils/Constants.h"


Enemy::Enemy(const glm::vec2& size, const glm::vec2& position) :
WorldObject(size, position, glm::vec2(0.0f, 0.0f), 0){}

void Enemy::setNextPosition(const ControlState &controlState, const WorldState &worldState, const float &deltaTime) {
    glm::vec2 velocity = ENEMY_MAX_VELOCITY * (glm::normalize(glm::vec2(worldState.playerX - position[0], worldState.playerY - position[1])));
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];
}

void Enemy::bulletCollision(Bullet &bullet) {
    glm::vec2 bulletPosition = bullet.getPosition();
    glm::vec2 bulletSize = bullet.getSize();

    float bulletLeftX = bulletPosition[0] - bulletSize[0];
    float bulletRightX = bulletPosition[0] + bulletSize[0];
    float enemyLeftX = position[0] - size[0];
    float enemyRightX = position[0] + size[0];
    float bulletLeftY = bulletPosition[1] - bulletSize[1];
    float bulletRightY = bulletPosition[1] + bulletSize[1];
    float enemyLeftY = position[1] - size[1];
    float enemyRightY = position[1] + size[1];

    if(!((enemyLeftX < bulletLeftX && enemyRightX < bulletLeftX) || (enemyLeftX > bulletRightX && enemyRightX > bulletRightX)) &&
       !((enemyLeftY < bulletLeftY && enemyRightY < bulletLeftY) || (enemyLeftY > bulletRightY && enemyRightY > bulletRightY))) {
        remove = true;
        bullet.removeObject();
    }
}
