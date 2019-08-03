#include "ConfigStore.h"

void ConfigStore::setScreenWidth(unsigned int width) {
    screenWidth = width;
}

void ConfigStore::setScreenHeight(unsigned int height) {
    screenHeight = height;
}

unsigned int ConfigStore::getScreenWidth() {
    return screenWidth;
}

unsigned int ConfigStore::getScreenHeight() {
    return screenHeight;
}
