#include "Game.h"

#include "../Interface/Window.h"
#include "../Utils/Constants.h"


Game::Game():
state(),
window(),
renderer(),
world(state){
    state.worldLowerX = -WORLD_SIZE_WIDTH;
    state.worldLowerY = -WORLD_SIZE_HEIGHT;
    state.worldUpperX = WORLD_SIZE_WIDTH;
    state.worldUpperY = WORLD_SIZE_HEIGHT;
    state.playerX = 0.0f;
    state.playerY = 0.0f;
}

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


