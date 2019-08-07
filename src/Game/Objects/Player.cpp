#include <utility>

#include "Player.h"

#include <iostream>


#define DECELERATION 320.0f
#define ACCELERATION 1500.0f
#define MAX_VELOCITY 300.0f


Player::Player(vmath::vec2 size, vmath::vec2 position, vmath::vec2 velocity, float angle) :
WorldObject(size, position,velocity, angle) {}

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

vmath::vec2 Player::setNextPosition(const ControlState &controlState, double deltaTime) {
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
    return position;
}


