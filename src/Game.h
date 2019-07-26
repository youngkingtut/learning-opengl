#pragma once


#include <GLFW/glfw3.h>
#include "ConfigStore.h"
#include "Window.h"


class Game {
public:
    explicit Game(ConfigStore config);
    ~Game();
    void initialize();
    void run();

private:
    Window window;
    ConfigStore config;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
};
