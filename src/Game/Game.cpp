#include "Game.h"

#include "../Interface/Window.h"
#include "../Utils/Constants.h"


Game::Game():
window(),
world(),
renderer(){}

void Game::run() {
    window.initialize();
    renderer.initialize();

    ControlState controlState;
    double time = glfwGetTime();

    while(window.ShouldExit()) {
        double timeNow = glfwGetTime();
        double delta = timeNow - time;

        // Locking frame rate to 60 fps
        if(delta > FPS_60) {
            time = timeNow;
            window.ProcessInput(controlState);
            world.update(controlState, delta);
            renderer.renderWorld(world);
            window.SwapBuffersAndPollEvents();
        }
    }
}


