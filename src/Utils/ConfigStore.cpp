#include "ConfigStore.h"


void ConfigStore::setScreenSize(float width, float height) {
    screenWidth = width;
    screenHeight = height;
}

void ConfigStore::setWorldSize(float width, float height) {
    worldWidth = width;
    worldHeight = height;
}

void ConfigStore::setPlayerSize(float width, float height) {
    playerWidth = width;
    playerHeight = height;
}

float ConfigStore::getScreenWidth() {
    return screenWidth;
}

float ConfigStore::getScreenHeight() {
    return screenHeight;
}

float ConfigStore::getWorldWidth() {
    return worldWidth;
}

float ConfigStore::getWorldHeight() {
    return worldHeight;
}

float ConfigStore::getPlayerWidth() {
    return playerWidth;
}

float ConfigStore::getPlayerHeight() {
    return playerHeight;
}
