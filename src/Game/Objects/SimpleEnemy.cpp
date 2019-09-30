#include "SimpleEnemy.h"
#include "../../Utils/Constants.h"


SimpleEnemy::SimpleEnemy(const glm::vec2& position) :
        WorldObject(position, glm::vec2(0.0F, 0.0F), glm::vec2(0.0F, 1.0F)){}

void SimpleEnemy::setNextPosition(const ControlState &controlState, const GameState &worldState, const double& deltaTime) {
    glm::vec2 velocity = ENEMY_MAX_VELOCITY * (glm::normalize(glm::vec2(worldState.playerX - position[0], worldState.playerY - position[1])));
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];
}

float SimpleEnemy::getRadius() const {
    return SIMPLE_ENEMY_RADIUS;
}
