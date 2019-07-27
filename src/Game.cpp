#include "Game.h"

#include <vmath.h>
#include <iostream>
#include <ctime>

#include "ShaderCompiler/ShaderCompiler.hpp"


void Game::initialize(ConfigStore config) {
    window.initialize(config);
    renderer.initialize();
}

void Game::run() {
    while (window.ShouldExit()) {
        window.ProcessInput();
        renderer.render();
        window.SwapBuffersAndPollEvents();
    }
}
