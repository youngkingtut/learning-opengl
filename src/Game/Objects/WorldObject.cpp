#include <utility>

#include "WorldObject.h"


WorldObject::WorldObject(vmath::vec2 s, vmath::vec2 p, vmath::vec2 v, const float &a)  :
size(std::move(s)),
position(std::move(p)),
velocity(std::move(v)),
angle(a){}

vmath::vec2 WorldObject::getPosition() const {
    return position;
}

vmath::vec2 WorldObject::getSize() const {
    return size;
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

bool WorldObject::shouldRemove() const {
    return remove;
}

void WorldObject::removeObject() {
    remove = true;
}
