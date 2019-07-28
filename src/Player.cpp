#include "Player.h"


#define VELOCITY_STEP 0.05f
#define VELOCITY_MAX 1.0f
#define DECELERATION_FACTOR 0.1f


void Player::initialize(float x, float y, float v_x, float v_y, const vmath::vec3& dir) {
    position.x = x;
    position.y = y;
    x_velocity = v_x;
    y_velocity = v_y;
    direction = vmath::normalize(dir);
}

void Player::updateXVelocity(VelocityUpdate vUpdate, double factor) {
    x_velocity = UpdateVelocity(x_velocity, vUpdate, factor);
}

void Player::updateYVelocity(VelocityUpdate vUpdate, double factor) {
    y_velocity = UpdateVelocity(y_velocity, vUpdate, factor);
}

float Player::UpdateVelocity(float velocity, VelocityUpdate vUpdate, double factor) {
    float updatedVelocity = velocity;

    switch(vUpdate) {
        case VelocityUpdate::INCREASE:
            updatedVelocity = velocity + (VELOCITY_STEP * factor);
            if(updatedVelocity > VELOCITY_MAX) {
                updatedVelocity = VELOCITY_MAX;
            }
            break;
        case VelocityUpdate::DECREASE:
            updatedVelocity = velocity - (VELOCITY_STEP * factor);
            if(updatedVelocity < -VELOCITY_MAX) {
                updatedVelocity = -VELOCITY_MAX;
            }
            break;
        case VelocityUpdate::TO_ZERO:
            if(velocity > 0.0f) {
                updatedVelocity = velocity - (DECELERATION_FACTOR * factor);
                if(updatedVelocity < 0.0f) {
                    updatedVelocity = 0.0f;
                }
            } else if (velocity < 0.0f) {
                updatedVelocity = velocity + (DECELERATION_FACTOR * factor);
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

void Player::updatePosition(Position new_position) {
    this->position.x = new_position.x;
    this->position.y = new_position.y;
}

float Player::getXPosition() {
    return position.x;
}

float Player::getYPosition() {
    return position.y;
}

float Player::getXVelocity() {
    return x_velocity;
}

float Player::getYVelocity() {
    return y_velocity;
}

Position Player::getNextPosition(double deltaTime) {
    float new_x = x_velocity * deltaTime + position.x;
    float new_y = y_velocity * deltaTime + position.y;
    return {new_x, new_y};
}

