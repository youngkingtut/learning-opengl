#include "Player.h"
#include "../../Utils/Constants.h"


Player::Player(const glm::vec2& size, const glm::vec2& position, const glm::vec2& velocity, float angle) :
WorldObject(size, position, velocity, angle) {}

void Player::updateXVelocity(VelocityUpdate vUpdate, double factor) {
    velocity[0] = updateVelocity(velocity[0], vUpdate, factor);
}

void Player::updateYVelocity(VelocityUpdate vUpdate, double factor) {
    velocity[1] = updateVelocity(velocity[1], vUpdate, factor);
}

float Player::updateVelocity(float velocity, VelocityUpdate vUpdate, double deltaTime) {
    float updatedVelocity = velocity;

    switch(vUpdate) {
        case VelocityUpdate::INCREASE:
            updatedVelocity = velocity + (ACCELERATION * deltaTime);
            break;
        case VelocityUpdate::TO_ZERO:
            if(velocity > 0.0f) {
                updatedVelocity = velocity - (DECELERATION * deltaTime);
                if(updatedVelocity < 0.0f) {
                    updatedVelocity = 0.0f;
                }
            } else if (velocity < 0.0f) {
                updatedVelocity = velocity + (DECELERATION * deltaTime);
                if(updatedVelocity > 0.0f) {
                    updatedVelocity = 0.0f;
                }
            } else {
                updatedVelocity = 0.0f;
            }
            break;
    }

    return updatedVelocity;
}

void Player::setNextPosition(const ControlState& controlState, const WorldState& worldState, const float& deltaTime) {
    glm::vec2 controlDirection = controlState.getMovementDirection();
    float controlMagnitude = controlState.getMovementMagnitude();

    // Update angle and normalize control direction if present
    if(controlMagnitude > 0) {
        controlDirection = glm::normalize(controlDirection);
        angle = calculateAngle(controlDirection);
        updateXVelocity(VelocityUpdate::INCREASE, controlDirection[0] * deltaTime);
        updateYVelocity(VelocityUpdate::INCREASE, controlDirection[1] * deltaTime);
    }

    if(controlDirection[0] == 0) {
        updateXVelocity(VelocityUpdate::TO_ZERO, deltaTime);
    }

    if(controlDirection[1] == 0) {
        updateYVelocity(VelocityUpdate::TO_ZERO, deltaTime);
    }

    if(glm::length(velocity) > PLAYER_MAX_VELOCITY) {
        velocity = glm::normalize(velocity) * PLAYER_MAX_VELOCITY;
    }

    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];

    // Boundary check
    if(position[0] + size[0] > worldState.worldUpperX) {
        position[0] = worldState.worldUpperX - size[0];
    } else if (position[0] - size[0] < worldState.worldLowerX) {
        position[0] = worldState.worldLowerX + size[0];
    }

    if(position[1] + size[1] > worldState.worldUpperY) {
        position[1] = worldState.worldUpperY - size[1];
    } else if (position[1] - size[1] < worldState.worldLowerY) {
        position[1] = worldState.worldLowerY + size[1];
    }
}

void Player::generateBullet(const ControlState& controlState, const float& deltaTime, std::vector<Bullet>& bullets) {
    coolDown += deltaTime;
    if(coolDown > PLAYER_BULLET_COOL_DOWN) {
        glm::vec2 bulletDirection = controlState.getBulletDirection();
        if(glm::length(bulletDirection) > 0) {
            coolDown = 0.0f;
            Bullet bullet = Bullet(glm::vec2(2.5, 2.5), position, BULLET_MAX_VELOCITY * glm::normalize(bulletDirection), 0);
            bullets.push_back(bullet);
        }
    }
}


