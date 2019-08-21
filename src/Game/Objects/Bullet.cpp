#include "Bullet.h"

#include "../../Utils/Constants.h"


Bullet::Bullet(const glm::vec2 &p, const glm::vec2 &v) :
WorldObject(p, v, v){}

void Bullet::setNextPosition(const ControlState &controlState, const GameState &worldState, const float &deltaTime) {
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];
    if(position[0] + BULLET_SIZE > worldState.worldUpperX || position[0] - BULLET_SIZE < worldState.worldLowerX) {
        remove = true;
    } else if (position[1] + BULLET_SIZE > worldState.worldUpperY || position[1] - BULLET_SIZE < worldState.worldLowerY) {
        remove = true;
    }
}

