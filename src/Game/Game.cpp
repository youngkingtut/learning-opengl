#include "Game.h"

#include <vmath.h>
#include <iostream>
#include <ctime>

#include "../Interface/Window.h"
#include "../Utils/Constants.h"


Game::Game(ConfigStore config):
window(config),
renderer(),
world(config.getWorldWidth(), config.getWorldHeight()),
controlState()
{

}
void Game::run() {
    window.initialize();
    renderer.initialize();

    double time = glfwGetTime();
    double time_plus_one = time + 1.0f;
    int frames = 0;

    while (window.ShouldExit()) {
        double time_now = glfwGetTime();
        double delta = time_now - time;

        // Get frames per second
        if(time_now > time_plus_one){
//            std::cout << frames << " FPS" << std::endl;
            time_plus_one = time_now + 1.0f;
            frames = 0;
        }

        // Locking frame rate to 60 fps
        if(delta > FPS_60) {
            time = time_now;
            window.ProcessInput(controlState);
            world.update(controlState, delta);
            renderer.render(world, window.GetAspectRatio());
            frames++;
            window.SwapBuffersAndPollEvents();
        }
    }
}


