#include "Bullet.h"


#define BULLET_VELOCITY 400.0f

Bullet::Bullet(vmath::vec2 s, vmath::vec2 p, vmath::vec2 v, float a) :
        position(std::move(p)),
        velocity(std::move(v)),
        angle(a),
        size(std::move(s)){}

Bullet::Bullet(vmath::vec2 s, vmath::vec2 d, vmath::vec2 p) :
    size(std::move(s)),
    position(std::move(p)),
    velocity(0),
    angle(0){
    angle = calculateAngle(d);
    velocity = BULLET_VELOCITY * vmath::normalize(d);
}

vmath::vec2 Bullet::setNextPosition(const ControlState &controlState, double deltaTime) {
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];
    return position;
}

vmath::vec2 Bullet::getSize() const {
    return size;
}

vmath::vec2 Bullet::getPosition() const {
    return position;
}

float Bullet::getAngle() const {
    return angle;
}

float Bullet::calculateAngle(vmath::vec2& dir) {
    float angle = vmath::angle(vmath::vec2(0.0, 1.0), dir);
    if(dir[0] > 0) {
        angle = -angle;
    }
    return vmath::degrees(angle);
}


