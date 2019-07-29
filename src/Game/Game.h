#pragma once

#include "../Interface/Window.h"
#include "../Interface/ControlState.h"
#include "../Renderer/Renderer.h"
#include "../Utils/ConfigStore.h"
#include "World.h"


class Game {
public:
    explicit Game(ConfigStore config);
    void run();

private:
    Window window;
    Renderer renderer;
    World world;
    ControlState controlState;
};
