#include <iostream>
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
    state.multiplier = 1;
    state.lives = 99;
}

void Game::run() {
    window.initialize();
    renderer.initialize();

    ControlState controlState;
    double time = glfwGetTime();

    while(window.ShouldExit()) {
        double timeNow = glfwGetTime();
        double delta = timeNow - time;
        time = timeNow;

        window.ProcessInput(controlState);

        if(state.lives > 0) {
            world.update(controlState, delta);
            renderer.renderWorld(world);
        } else {
            renderer.renderGameOverScreen(world);
        }

        window.SwapBuffersAndPollEvents();
    }
}


