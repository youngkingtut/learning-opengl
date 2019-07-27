#include "Game.h"

#include <vmath.h>
#include <iostream>
#include <ctime>

#include "Window.h"

void Game::initialize(ConfigStore config) {
    window.initialize(config);
    renderer.initialize();
    world.initialize(config);
}

void Game::run() {
    while (window.ShouldExit()) {
        window.ProcessInput(controlState);
        world.updateFromInput(controlState);
        renderer.render(window.GetAspectRatio());
        window.SwapBuffersAndPollEvents();
    }
}
