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
    double time = glfwGetTime();

    while (window.ShouldExit()) {
        double time_now = glfwGetTime();
        double delta = time_now - time;
        time = time_now;

        window.ProcessInput(controlState);
        world.updateFromInput(controlState, delta);
        renderer.render(world, window.GetAspectRatio());
        window.SwapBuffersAndPollEvents();
    }
}
