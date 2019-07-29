#pragma once

#include <fstream>
#include <map>
#include <string>


class ConfigStore
{
public:
    ConfigStore() = default;

    void setScreenWidth(unsigned int width);
    void setScreenHeight(unsigned int height);
    void setWorldWidth(float width);
    void setWorldHeight(float height);

    unsigned int getScreenWidth();
    unsigned int getScreenHeight();
    float getWorldWidth();
    float getWorldHeight();

private:
    unsigned int screenWidth;
    unsigned int screenHeight;
    float worldWidth;
    float worldHeight;

};

