#include "Player.h"


#define VELOCITY_STEP 0.05f
#define VELOCITY_MAX 20.0f


void Player::initialize(float x, float y, float v_x, float v_y, const vmath::vec3& dir) {
    x_position = x;
    y_position = y;
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
        case VelocityUpdate::INCREASE_TO_ZERO:
            if(velocity < 0.0f){
                updatedVelocity = velocity + (VELOCITY_STEP * factor);
                if(updatedVelocity > 0.0f) {
                    updatedVelocity = 0.0f;
                }
            }
            break;
        case VelocityUpdate::DECREASE:
            updatedVelocity = velocity - (VELOCITY_STEP * factor);
            if(updatedVelocity < -VELOCITY_MAX) {
                updatedVelocity = -VELOCITY_MAX;
            }
            break;
        case VelocityUpdate::DECREASE_TO_ZERO:
            if(velocity > 0.0f) {
                updatedVelocity = velocity - (VELOCITY_STEP * factor);
                if(updatedVelocity < 0.0f) {
                    updatedVelocity = 0.0f;
                }
            }
            break;
        case VelocityUpdate::ZERO:
            updatedVelocity = 0;
            break;
    }

    return updatedVelocity;
}

void Player::updatePosition(double deltaTime) {
    x_position = x_velocity * deltaTime + x_position;
    y_position = y_velocity * deltaTime + y_position;
}

float Player::getXPosition() {
    return x_position;
}

float Player::getYPosition() {
    return y_position;
}

float Player::getXVelocity() {
    return x_velocity;
}

float Player::getYVelocity() {
    return y_velocity;
}

