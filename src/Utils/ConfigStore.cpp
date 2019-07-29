#include "ConfigStore.h"

void ConfigStore::setScreenWidth(unsigned int width) {
    screenWidth = width;
}

void ConfigStore::setScreenHeight(unsigned int height) {
    screenHeight = height;
}

void ConfigStore::setWorldWidth(float width) {
    worldWidth = width;
}

void ConfigStore::setWorldHeight(float height) {
    worldHeight = height;
}


unsigned int ConfigStore::getScreenWidth() {
    return screenWidth;
}

unsigned int ConfigStore::getScreenHeight() {
    return screenHeight;
}

float ConfigStore::getWorldWidth() {
    return worldWidth;
}

float ConfigStore::getWorldHeight() {
    return worldWidth;
}


