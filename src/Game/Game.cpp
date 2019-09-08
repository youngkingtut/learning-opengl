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
    std::vector<double> loopTime;
    double time = glfwGetTime();

    while(window.ShouldExit()) {
        double timeNow = glfwGetTime();
        double delta = timeNow - time;
        time = timeNow;

        loopTime.emplace_back(delta);

        window.ProcessInput(controlState);

        if(state.lives > 0) {
            world.update(controlState, delta);
            renderer.renderWorld(world);
        } else {
            renderer.renderGameOverScreen(world);
        }

        window.SwapBuffersAndPollEvents();
    }

    double totalTime = 0.0f;
    for(double t : loopTime) {
        totalTime += t;
    }
    double averageTime = loopTime.empty() ? 0.0f : totalTime / loopTime.size();
    double averageFps = averageTime == 0.0f ? 0.0f : 1 / averageTime;

    std::cout << "Average loop time: " << averageTime << std::endl;
    std::cout << "Average frames per second: " << averageFps << std::endl;
}


