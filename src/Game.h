#pragma once

#include "ConfigStore.h"
#include "Window.h"
#include "Renderer.h"
#include "World.h"
#include "ControlState.h"


class Game {
public:
    void initialize(ConfigStore config);
    void run();

private:
    Window window;
    Renderer renderer;
    World world;
    ControlState controlState;
};
