#include <iostream>
#include "Game.h"

#include "../Interface/Window.h"


void Game::run() {
    World world = World();
    Window window = Window();
    Renderer renderer = Renderer();

    window.initialize();
    renderer.initialize();

    GameState gameState = GameState::GAME_RUNNING;
    ControlState controlState;
    std::vector<double> loopTime;
    double time = glfwGetTime();

    while(window.ShouldExit()) {
        double timeNow = glfwGetTime();
        double delta = timeNow - time;
        time = timeNow;

        loopTime.emplace_back(delta);
        window.ProcessInput(controlState);

        switch(gameState){
            case GameState::GAME_RUNNING:
                gameState = world.update(controlState, delta);
                renderer.renderWorld(world);
                break;
            case GameState::GAME_OVER:
                renderer.renderGameOverScreen(world);
                break;
            case GameState::GAME_PAUSE:
                break;
            case GameState::MENU:
                break;
        }


        window.SwapBuffersAndPollEvents();
    }

    double totalTime = 0.0F;
    for(double t : loopTime) {
        totalTime += t;
    }
    double averageTime = loopTime.empty() ? 0.0F : totalTime / loopTime.size();
    double averageFps = averageTime == 0.0F ? 0.0F : 1 / averageTime;

    std::cout << "Average loop time: " << averageTime << std::endl;
    std::cout << "Average frames per second: " << averageFps << std::endl;
}
