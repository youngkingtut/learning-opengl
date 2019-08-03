#pragma once

#include <fstream>
#include <map>
#include <string>


class ConfigStore {
public:
    ConfigStore() = default;

    void setScreenWidth(unsigned int width);
    void setScreenHeight(unsigned int height);

    unsigned int getScreenWidth();
    unsigned int getScreenHeight();

private:
    unsigned int screenWidth;
    unsigned int screenHeight;
};
