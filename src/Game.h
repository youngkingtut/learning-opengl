#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ConfigStore.h"


class Game {
public:
    explicit Game(ConfigStore config);
    ~Game();
    void initialize();
    void run();

private:
    GLFWwindow* window;
    ConfigStore config;
    float aspectRatio;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;


    void processInput();
};
