#include "Bullet.h"

#include "../../Utils/Constants.h"


Bullet::Bullet(const glm::vec2 &p, const glm::vec2 &v, const glm::vec2 &d) :
WorldObject(p, v, d){}

void Bullet::setNextPosition(const GameControlState &controlState, const WorldState &worldState, const double& deltaTime) {
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];
    if(position[0] + BULLET_RADIUS > worldState.worldUpperX || position[0] - BULLET_RADIUS < worldState.worldLowerX) {
        remove = true;
    } else if (position[1] + BULLET_RADIUS > worldState.worldUpperY || position[1] - BULLET_RADIUS < worldState.worldLowerY) {
        remove = true;
    }
}

float Bullet::getRadius() const {
    return BULLET_RADIUS;
}

