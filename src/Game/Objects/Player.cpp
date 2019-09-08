#include "Player.h"
#include <glm/gtx/projection.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include "../../Utils/Constants.h"


Player::Player(const glm::vec2& position, const glm::vec2& velocity, const glm::vec2 &direction) :
WorldObject(position, velocity, direction) {}

void Player::updateXVelocity(float targetVelocity, double deltaTime) {
    velocity[0] = updateVelocity(velocity[0], targetVelocity, deltaTime);
}

void Player::updateYVelocity(float targetVelocity, double deltaTime) {
    velocity[1] = updateVelocity(velocity[1], targetVelocity, deltaTime);
}

float Player::updateVelocity(float velocity, float targetVelocity, double deltaTime) {
    float updatedVelocity = velocity;

    if(targetVelocity > 0) {
        if(updatedVelocity > targetVelocity) {
            updatedVelocity -= DECELERATION * deltaTime;
            if(updatedVelocity < targetVelocity) {
                updatedVelocity = targetVelocity;
            }
        } else {
            updatedVelocity += ACCELERATION * deltaTime;
            if(updatedVelocity < 0) {
                updatedVelocity += DECELERATION * deltaTime;
            }
            if(updatedVelocity > targetVelocity) {
                updatedVelocity = targetVelocity;
            }
        }
    } else if (targetVelocity < 0) {
        if(updatedVelocity < targetVelocity) {
            updatedVelocity += DECELERATION * deltaTime;
            if(updatedVelocity > targetVelocity) {
                updatedVelocity = targetVelocity;
            }
        } else {
            updatedVelocity -= ACCELERATION * deltaTime;
            if(updatedVelocity > 0) {
                updatedVelocity -= DECELERATION * deltaTime;
            }
            if(updatedVelocity < targetVelocity) {
                updatedVelocity = targetVelocity;
            }
        }
    } else {
        if(updatedVelocity > 0) {
            updatedVelocity -= DECELERATION * deltaTime;
            if(updatedVelocity < targetVelocity) {
                updatedVelocity = targetVelocity;
            }
        } else {
            updatedVelocity += DECELERATION * deltaTime;
            if(updatedVelocity > targetVelocity) {
                updatedVelocity = targetVelocity;
            }
        }
    }
    return updatedVelocity;
}

void Player::setNextPosition(const ControlState& controlState, const GameState& worldState, const float& deltaTime) {
    glm::vec2 controlDirection = controlState.getMovementDirection();
    float controlMagnitude = controlState.getMovementMagnitude();

    // Update direction
    if(controlMagnitude > 0) {
        direction = glm::normalize(controlDirection);
        glm::vec2 maxVelocity = (glm::length(controlDirection) > PLAYER_MAX_VELOCITY_THRESHOLD)? PLAYER_MAX_VELOCITY * direction : PLAYER_MAX_VELOCITY * controlDirection;
        updateXVelocity(maxVelocity[0], deltaTime);
        updateYVelocity(maxVelocity[1], deltaTime);
        if(glm::length(velocity) > PLAYER_MAX_VELOCITY) {
            velocity = PLAYER_MAX_VELOCITY * direction;
        }
    }

    if(controlDirection[0] == 0) {
        updateXVelocity(0.0f, deltaTime);
    }

    if(controlDirection[1] == 0) {
        updateYVelocity(0.0f, deltaTime);
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
            glm::vec2 bulletFirstPosition = position + (PLAYER_RADIUS + PLAYER_BOUNDARY) * glm::rotate(normalizedBulletDirection, BULLET_SPREAD);
            glm::vec2 bulletSecondPosition = position + (PLAYER_RADIUS + PLAYER_BOUNDARY) * glm::rotate(normalizedBulletDirection, -BULLET_SPREAD);

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
