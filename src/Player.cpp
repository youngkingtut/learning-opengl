#include "Player.h"

#include <iostream>


#define DECELERATION 10.0f
#define ACCELERATION 13.0f
#define MAX_VELOCITY 4.0f


Player::Player(float x, float y, float v_x, float v_y, const vmath::vec2 &dir):
position(x, y),
x_velocity(v_x),
y_velocity(v_y),
direction(vmath::normalize(dir)){
    angle = calculateAngle(direction);
}

void Player::updateXVelocity(VelocityUpdate vUpdate, double factor) {
    x_velocity = updateVelocity(x_velocity, vUpdate, factor);
}

void Player::updateYVelocity(VelocityUpdate vUpdate, double factor) {
    y_velocity = updateVelocity(y_velocity, vUpdate, factor);
}

float Player::updateVelocity(float velocity, VelocityUpdate vUpdate, double deltaTime) {
    // todo velocity needs to be normalized
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

void Player::setPosition(Position new_position) {
    this->position.x = new_position.x;
    this->position.y = new_position.y;
}

Position Player::getPosition() {
    return position;
}

Position Player::getNextPosition(ControlState controlState, double deltaTime) {
    double upScale = controlState.getUp();
    double downScale = controlState.getDown();
    double leftScale = controlState.getLeft();
    double rightScale = controlState.getRight();

    if(x_velocity >= 0.0f) {
        updateXVelocity(VelocityUpdate::INCREASE, rightScale * deltaTime);
        if(leftScale > 0.0f) {
            updateXVelocity(VelocityUpdate::TO_ZERO, deltaTime);
            updateXVelocity(VelocityUpdate::DECREASE, leftScale * deltaTime);
        }
    } else {
        updateXVelocity(VelocityUpdate::DECREASE, leftScale * deltaTime);
        if(rightScale > 0.0f) {
            updateXVelocity(VelocityUpdate::TO_ZERO, deltaTime);
            updateXVelocity(VelocityUpdate::INCREASE, rightScale * deltaTime);
        }
    }

    if(leftScale == 0.0f && rightScale == 0.0f) {
        updateXVelocity(VelocityUpdate::TO_ZERO, deltaTime);
    }

    if(y_velocity >= 0.0f) {
        updateYVelocity(VelocityUpdate::INCREASE, upScale * deltaTime);
        if(downScale > 0.0f) {
            updateYVelocity(VelocityUpdate::TO_ZERO, deltaTime);
            updateYVelocity(VelocityUpdate::DECREASE, downScale * deltaTime);
        }
    } else {
        updateYVelocity(VelocityUpdate::DECREASE, downScale * deltaTime);
        if(upScale > 0.0f) {
            updateYVelocity(VelocityUpdate::TO_ZERO, deltaTime);
            updateYVelocity(VelocityUpdate::INCREASE, upScale * deltaTime);
        }
    }

    if(upScale == 0.0f && downScale == 0.0f) {
        updateYVelocity(VelocityUpdate::TO_ZERO, deltaTime);
    }

    if(upScale > 0 || downScale > 0 || rightScale > 0 || leftScale > 0) {
        direction = vmath::normalize(vmath::vec2(rightScale - leftScale, upScale - downScale));
        angle = calculateAngle(direction);
    }

    float new_x = x_velocity * deltaTime + position.x;
    float new_y = y_velocity * deltaTime + position.y;
    return {new_x, new_y};
}

float Player::getAngle() {
    return angle;
}

float Player::calculateAngle(vmath::vec2& dir) {
    float angle = vmath::angle(vmath::vec2(1.0, 0.0), dir);
    if(dir[1] < 0) {
        angle += M_PI;
    }
    return vmath::degrees(angle);
}
