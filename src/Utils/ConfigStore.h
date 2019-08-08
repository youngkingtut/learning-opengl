#pragma once

#include <fstream>
#include <map>
#include <string>


class ConfigStore {
public:
    ConfigStore() = default;

    void setScreenSize(float width, float height);
    void setWorldSize(float width, float height);
    void setPlayerSize(float width, float height);

    float getScreenWidth();
    float getScreenHeight();
    float getWorldWidth();
    float getWorldHeight();
    float getPlayerWidth();
    float getPlayerHeight();

private:
    float screenWidth;
    float screenHeight;
    float worldWidth;
    float worldHeight;
    float playerWidth;
    float playerHeight;
};
