#include "Bullet.h"


Bullet::Bullet(const glm::vec2 &s, const glm::vec2 &p, const glm::vec2 &v, float a) :
WorldObject(s, p, v, a){}

void Bullet::setNextPosition(const ControlState &controlState, const GameState &worldState, const float &deltaTime) {
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];
    if(position[0] + size[0] > worldState.worldUpperX || position[0] - size[0] < worldState.worldLowerX) {
        remove = true;
    } else if (position[1] + size[1] > worldState.worldUpperY || position[1] - size[1] < worldState.worldLowerY) {
        remove = true;
    }
}

