#pragma once

#include "../Interface/Window.h"
#include "../Renderer/Renderer.h"
#include "World.h"


class Game {
public:
    explicit Game();
    void run();

private:
    GameState state;
    Window window;
    Renderer renderer;
    World world;
};
