#include <glm/gtx/vector_angle.hpp>

#include "WorldObject.h"


WorldObject::WorldObject(const glm::vec2 &p, const glm::vec2 &v, const glm::vec2 &d)  :
position(p),
velocity(v),
direction(d){}

glm::vec2 WorldObject::getPosition() const {
    return position;
}

bool WorldObject::shouldRemove() const {
    return remove;
}

void WorldObject::removeObject() {
    remove = true;
}

float WorldObject::getAngle() const {
    glm::vec2 up = glm::vec2(0, 1);
    float angle = glm::angle(this->direction, up);
    if(direction[0] > 0) {
        angle = -angle;
    }
    return angle;
}

bool WorldObject::collision(const WorldObject& object) {
    return glm::distance(position, object.getPosition()) <= object.getRadius() + this->getRadius();
}

void WorldObject::zeroVelocity() {
    velocity[0] = 0.0F;
    velocity[1] = 0.0F;
}

WorldObject::WorldObject() {
    position = glm::vec2(0, 0);
    velocity = glm::vec2(0, 0);
    direction = glm::vec2(0, 0);
    remove = false;
}
