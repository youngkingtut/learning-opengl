#include "GameOverControlState.h"

void GameOverControlState::setReset(bool r) {
    this->reset = r;
}

bool GameOverControlState::getReset() const {
    return reset;
}
