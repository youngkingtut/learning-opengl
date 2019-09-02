#include "Player.h"
#include <glm/gtx/projection.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../../Utils/Constants.h"


Player::Player(const glm::vec2& position, const glm::vec2& velocity, const glm::vec2 &direction) :
WorldObject(position, velocity, direction) {}

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

void Player::setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) {
    glm::vec2 controlDirection = controlState.getMovementDirection();
    float controlMagnitude = controlState.getMovementMagnitude();

    // Update direction
    if(controlMagnitude > 0) {
        direction = glm::normalize(controlDirection);
        updateXVelocity(VelocityUpdate::INCREASE, direction[0] * deltaTime);
        updateYVelocity(VelocityUpdate::INCREASE, direction[1] * deltaTime);
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
    if(position[0] + PLAYER_RADIUS > worldState.worldUpperX) {
        position[0] = worldState.worldUpperX - PLAYER_RADIUS;
    } else if (position[0] - PLAYER_RADIUS < worldState.worldLowerX) {
        position[0] = worldState.worldLowerX + PLAYER_RADIUS;
    }

    if(position[1] + PLAYER_RADIUS > worldState.worldUpperY) {
        position[1] = worldState.worldUpperY - PLAYER_RADIUS;
    } else if (position[1] - PLAYER_RADIUS < worldState.worldLowerY) {
        position[1] = worldState.worldLowerY + PLAYER_RADIUS;
    }
}

void Player::generateBullet(const ControlState& controlState, const float& deltaTime, std::vector<Bullet>& bullets) {
    coolDown += deltaTime;
    if(coolDown > PLAYER_BULLET_COOL_DOWN) {
        glm::vec2 bulletDirection = controlState.getBulletDirection();
        if(glm::length(bulletDirection) > 0) {
            coolDown = 0.0f;
            glm::vec2 bulletVelocity;
            glm::vec2 normalizedBulletDirection = glm::normalize(bulletDirection);
            if(glm::length(velocity) == 0) {
                bulletVelocity = BULLET_MAX_VELOCITY * normalizedBulletDirection;
            } else {
                bulletVelocity = BULLET_MAX_VELOCITY * normalizedBulletDirection + glm::proj(velocity, normalizedBulletDirection);
            }
            glm::vec2 bulletFirstPosition = position + (PLAYER_RADIUS + PLAYER_BOUNDARY) * glm::rotate(bulletDirection, 0.4f);
            glm::vec2 bulletSecondPosition = position + (PLAYER_RADIUS + PLAYER_BOUNDARY) * glm::rotate(bulletDirection, -0.4f);

            Bullet bulletFirst = Bullet(bulletFirstPosition, bulletVelocity, normalizedBulletDirection);
            Bullet bulletSecond = Bullet(bulletSecondPosition, bulletVelocity, normalizedBulletDirection);
            bullets.push_back(bulletFirst);
            bullets.push_back(bulletSecond);

        }
    }
}

bool Player::enemyCollision(const Enemy &enemy) {
    return collision(enemy, PLAYER_RADIUS, ENEMY_RADIUS);
}
