#include "Player.h"

#include <iostream>


#define DECELERATION 10.0f
#define ACCELERATION 13.0f
#define MAX_VELOCITY 4.0f


Player::Player():
    position(0, 0),
    velocity(0, 0),
    angle(0){}

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

void Player::setPosition(vmath::vec2 p) {
    position[0] = p[0];
    position[1] = p[1];
}

vmath::vec2 Player::getPosition() {
    return position;
}

vmath::vec2 Player::getNextPosition(ControlState controlState, double deltaTime) {
    vmath::vec2 controlDirection = vmath::vec2(controlState.getRight() - controlState.getLeft(), controlState.getUp() - controlState.getDown());

    // Update angle and normalize control direction if present
    if(vmath::length(controlDirection) > 0) {
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
    return position;
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
