#include "WorldObject.h"

WorldObject::WorldObject(vmath::vec2 s, vmath::vec2 p, vmath::vec2 v, float a) :
size(s),
position(p),
velocity(v),
angle(a){}

vmath::vec2 WorldObject::getSize() const {
    return size;
}

vmath::vec2 WorldObject::getPosition() const {
    return position;
}

vmath::vec2 WorldObject::getVelocity() const {
    return velocity;
}

float WorldObject::getAngle() const {
    return angle;
}

float WorldObject::calculateAngle(vmath::vec2& dir) {
    float angle = vmath::angle(vmath::vec2(0.0, 1.0), dir);
    if(dir[0] > 0) {
        angle = -angle;
    }
    return vmath::degrees(angle);
}

void WorldObject::setPosition(const vmath::vec2& pos) {
    this->position = pos;
}
