#include "ConfigStore.h"


void ConfigStore::setScreenWidth(int width) {
    this->screenWidth = width;
}

int ConfigStore::getScreenWidth() {
    return this->screenWidth;
}

void ConfigStore::setScreenHeight(int height) {
    this->screenHeight = height;
}

int ConfigStore::getScreenHeight() {
    return this->screenHeight;
}
