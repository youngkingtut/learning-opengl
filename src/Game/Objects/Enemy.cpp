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
    if(bullet.shouldRemove()) {
        return;
    }
    glm::vec2 bulletPosition = bullet.getPosition();

    float bulletLeftX = bulletPosition[0] - BULLET_SIZE;
    float bulletRightX = bulletPosition[0] + BULLET_SIZE;
    float enemyLeftX = position[0] - ENEMY_SIZE;
    float enemyRightX = position[0] + ENEMY_SIZE;
    float bulletLeftY = bulletPosition[1] - BULLET_SIZE;
    float bulletRightY = bulletPosition[1] + BULLET_SIZE;
    float enemyLeftY = position[1] - ENEMY_SIZE;
    float enemyRightY = position[1] + ENEMY_SIZE;

    if(!((enemyLeftX < bulletLeftX && enemyRightX < bulletLeftX) || (enemyLeftX > bulletRightX && enemyRightX > bulletRightX)) &&
       !((enemyLeftY < bulletLeftY && enemyRightY < bulletLeftY) || (enemyLeftY > bulletRightY && enemyRightY > bulletRightY))) {
        remove = true;
        bullet.removeObject();
    }
}
