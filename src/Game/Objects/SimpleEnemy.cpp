#include "SimpleEnemy.h"

#include <glm/gtx/rotate_vector.hpp>

#include "../../Utils/Constants.h"
#include "../../Utils/Random.h"


SimpleEnemy::SimpleEnemy(const glm::vec2& position) :
        WorldObject(position, glm::vec2(0.0F, 0.0F), glm::vec2(0.0F, 1.0F)) {
    rotationSpeed = Random::getRandomFloat(SIMPLE_ENEMY_MIN_ROTATION_SPEED, SIMPLE_ENEMY_MAX_ROTATION_SPEED);
    if(Random::getRandomBool()) {
        rotationSpeed = -rotationSpeed;
    }
    direction = glm::rotate(glm::vec2(1.0F, 0.0F), Random::getRandomFloat(0.0F, static_cast<float>(M_2_PI)));
    switch(Random::getRandomInt(0, 4)) {
        case 0:
            velocity = glm::vec2(SIMPLE_ENEMY_VELOCITY, 0.0F);
            break;
        case 1:
            velocity = glm::vec2(-SIMPLE_ENEMY_VELOCITY, 0.0F);
            break;
        case 2:
            velocity = glm::vec2(0.0F, SIMPLE_ENEMY_VELOCITY);
            break;
        case 3:
        default:
            velocity = glm::vec2(0.0F, -SIMPLE_ENEMY_VELOCITY);
            break;
    }
}

void SimpleEnemy::setNextPosition(const ControlState &controlState, const WorldState &worldState, const double& deltaTime) {
    direction = glm::rotate(direction, rotationSpeed * static_cast<float>(deltaTime));
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];

    // Boundary check
    bool boundaryCross = false;
    if(position[0] + SIMPLE_ENEMY_RADIUS > worldState.worldUpperX) {
        position[0] = worldState.worldUpperX - SIMPLE_ENEMY_RADIUS;
        boundaryCross = true;
    } else if (position[0] - SIMPLE_ENEMY_RADIUS < worldState.worldLowerX) {
        position[0] = worldState.worldLowerX + SIMPLE_ENEMY_RADIUS;
        boundaryCross = true;
    }

    if(position[1] + SIMPLE_ENEMY_RADIUS > worldState.worldUpperY) {
        position[1] = worldState.worldUpperY - SIMPLE_ENEMY_RADIUS;
        boundaryCross = true;
    } else if (position[1] - SIMPLE_ENEMY_RADIUS < worldState.worldLowerY) {
        position[1] = worldState.worldLowerY + SIMPLE_ENEMY_RADIUS;
        boundaryCross = true;
    }

    // Flip velocity
    if(boundaryCross) {
        velocity = glm::rotate(velocity, static_cast<float>(M_PI));
        rotationSpeed = -rotationSpeed;
    }
}

float SimpleEnemy::getRadius() const {
    return SIMPLE_ENEMY_RADIUS;
}
