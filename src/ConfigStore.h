#pragma once

#include <fstream>
#include <map>
#include <string>


class ConfigStore
{
public:
    ConfigStore() = default;

    void setScreenWidth(int width);
    void setScreenHeight(int height);

    int getScreenWidth();
    int getScreenHeight();

private:
    int screenWidth;
    int screenHeight;

};

