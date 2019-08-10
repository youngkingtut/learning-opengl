#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include "Player.h"

#include "../../Utils/Constants.h"


Player::Player(vmath::vec2 size, vmath::vec2 position, vmath::vec2 velocity, float angle) :
WorldObject(std::move(size), std::move(position), std::move(velocity), angle) {}

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
    vmath::vec2 controlDirection = controlState.getMovementDirection();
    float controlMagnitude = controlState.getMovementMagnitude();

    // Update angle and normalize control direction if present
    if(controlMagnitude > 0) {
        controlDirection = vmath::normalize(controlDirection);
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

    if(vmath::length(velocity) > MAX_VELOCITY) {
        velocity = vmath::normalize(velocity) * MAX_VELOCITY;
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
    float bound = PLAYER_BULLET_COOL_DOWN;
    if(coolDown > bound) {
        vmath::vec2 bulletDirection = controlState.getBulletDirection();
        if(vmath::length(bulletDirection) > 0) {
            Bullet bullet = Bullet(vmath::vec2(5, 5), position, BULLET_VELOCITY * vmath::normalize(bulletDirection), 0);
            bullets.push_back(bullet);
        }
    }
}


