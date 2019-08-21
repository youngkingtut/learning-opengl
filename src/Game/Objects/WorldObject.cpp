#include <glm/gtx/vector_angle.hpp>

#include "WorldObject.h"


WorldObject::WorldObject(const glm::vec2 &p, const glm::vec2 &v, const glm::vec2 &d)  :
position(p),
velocity(v),
direction(d){}

glm::vec2 WorldObject::getPosition() const {
    return position;
}

glm::vec2 WorldObject::getDirection() const {
    return direction;
}

bool WorldObject::shouldRemove() const {
    return remove;
}

void WorldObject::removeObject() {
    remove = true;
}
