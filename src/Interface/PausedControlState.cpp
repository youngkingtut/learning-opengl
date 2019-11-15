#include "PausedControlState.h"


void PausedControlState::setPausePress(bool status) {
    this->pausePress = status;
}

void PausedControlState::setPauseRelease(bool status) {
    this->pauseRelease = status;
}

bool PausedControlState::getPausePress() const {
    return this->pausePress;
}

bool PausedControlState::getPauseRelease() const {
    return this->pauseRelease;
}
