#include "Bullet.h"


Bullet::Bullet(const vmath::vec2 &s, const vmath::vec2 &p, const vmath::vec2 &v, float a) :
WorldObject(s, p, v, a),
remove(false){}

vmath::vec2 Bullet::setNextPosition(const ControlState &controlState, double deltaTime) {
    position[0] = velocity[0] * deltaTime + position[0];
    position[1] = velocity[1] * deltaTime + position[1];
    return position;
}

bool Bullet::shouldRemove() const {
    return remove;
}

void Bullet::setRemove(bool r) {
    remove = r;
}
