#pragma once

#include "ConfigStore.h"
#include "Window.h"
#include "Renderer.h"


class Game {
public:
    void initialize(ConfigStore config);
    void run();

private:
    Window window;
    Renderer renderer;
};
