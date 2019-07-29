#include "ControlState.h"


void ControlState::setUp(float u) {
    up = u;
}

void ControlState::setDown(float d) {
    down = d;
}

void ControlState::setRight(float r) {
    right = r;
}

void ControlState::setLeft(float l) {
    left = l;
}

float ControlState::getUp() {
    return up;
}

float ControlState::getDown() {
    return down;
}

float ControlState::getRight() {
    return right;
}

float ControlState::getLeft() {
    return left;
}
