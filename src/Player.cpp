#include "Player.h"


#define DECELERATION 10.0f
#define ACCELERATION 10.0f
#define MAX_VELOCITY 3.0f


Player::Player(float x, float y, float v_x, float v_y, const vmath::vec3 &dir): position(x, y) {
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

float Player::UpdateVelocity(float velocity, VelocityUpdate vUpdate, double deltaTime) {
    float updatedVelocity = velocity;

    switch(vUpdate) {
        case VelocityUpdate::INCREASE:
            updatedVelocity = velocity + (ACCELERATION * deltaTime);
            if(updatedVelocity > MAX_VELOCITY) {
                updatedVelocity = MAX_VELOCITY;
            }
            break;
        case VelocityUpdate::DECREASE:
            updatedVelocity = velocity - (ACCELERATION * deltaTime);
            if(updatedVelocity < -MAX_VELOCITY) {
                updatedVelocity = -MAX_VELOCITY;
            }
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

void Player::updatePosition(Position new_position) {
    this->position.x = new_position.x;
    this->position.y = new_position.y;
}

Position Player::getPosition() {
    return position;
}

float Player::getXVelocity() {
    return x_velocity;
}

float Player::getYVelocity() {
    return y_velocity;
}

Position Player::getNextPosition(ControlState controlState, double deltaTime) {
    double upScale = controlState.getUp();
    double downScale = controlState.getDown();
    double leftScale = controlState.getLeft();
    double rightScale = controlState.getRight();

    updateXVelocity(VelocityUpdate::INCREASE, rightScale * deltaTime);
    updateXVelocity(VelocityUpdate::DECREASE, leftScale * deltaTime);

    updateYVelocity(VelocityUpdate::INCREASE, upScale * deltaTime);
    updateYVelocity(VelocityUpdate::DECREASE, downScale * deltaTime);

    if(upScale == 0.0f && downScale == 0.0f) {
        updateYVelocity(VelocityUpdate::TO_ZERO, deltaTime);
    }

    if(leftScale == 0.0f && rightScale == 0.0f) {
        updateXVelocity(VelocityUpdate::TO_ZERO, deltaTime);
    }

    float new_x = x_velocity * deltaTime + position.x;
    float new_y = y_velocity * deltaTime + position.y;
    return {new_x, new_y};
}
