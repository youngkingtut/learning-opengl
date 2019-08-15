#include <glm/gtx/vector_angle.hpp>

#include "WorldObject.h"


WorldObject::WorldObject(const glm::vec2& s, const glm::vec2& p, const glm::vec2& v, const float &a)  :
size(s),
position(p),
velocity(v),
angle(a){}

glm::vec2 WorldObject::getPosition() const {
    return position;
}

glm::vec2 WorldObject::getSize() const {
    return size;
}

float WorldObject::getAngle() const {
    return angle;
}

float WorldObject::calculateAngle(glm::vec2& dir) {
    float angle = glm::angle(glm::vec2(0.0, 1.0), dir);
    if(dir[0] > 0) {
        angle = -angle;
    }
    return angle;
}

bool WorldObject::shouldRemove() const {
    return remove;
}

void WorldObject::removeObject() {
    remove = true;
}
