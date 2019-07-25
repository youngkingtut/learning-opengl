#include "Game.h"

#include <vmath.h>
#include <iostream>
#include <ctime>

#include "ShaderCompiler/ShaderCompiler.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

Game::Game(ConfigStore config) {
    this->config = config;
    aspectRatio = (float)config.getScreenWidth() / config.getScreenHeight();
    window = nullptr;
    vao = 0;
    vbo = 0;
    ebo = 0;
}

void Game::initialize() {
    glfwInit();
#if __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(config.getScreenWidth(), config.getScreenHeight(), "LearningOpenGL", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // todo create exceptions
        throw std::exception();
    }


    glViewport(0, 0, config.getScreenWidth(), config.getScreenHeight());
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // cube
    static const GLfloat vertices[] = {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            0.25f, -0.25f, -0.25f,
            0.25f,  0.25f, -0.25f,
            0.25f, -0.25f,  0.25f,
            0.25f,  0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
    };

    static const GLuint indicies[] = {
            0, 1, 2,
            2, 3, 0,

            2, 4, 3,
            4, 5, 3,

            4, 6, 5,
            6, 7, 5,

            6, 1, 7,
            1, 0, 7,

            6, 4, 2,
            2, 1, 6,

            0, 3, 5,
            5, 7, 0,
    };


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}


void Game::run() {
    GLuint shaderProgram = LoadShaders("Shaders/shader.vert", "Shaders/shader.frag");
    GLint mv_location = glGetUniformLocation(shaderProgram, "mv_matrix");
    GLint proj_location = glGetUniformLocation(shaderProgram, "proj_matrix");

    while (!glfwWindowShouldClose(window)) {
        float currentTime = (float)std::clock() / CLOCKS_PER_SEC;
        processInput();
        static const GLfloat one = 1.0f;
        float x_translate = 0.0f;
        float y_translate = 0.0f;

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearBufferfv(GL_DEPTH, 0, &one);

        vmath::mat4 proj_matrix = vmath::perspective(50.0f, this->aspectRatio, 0.1f, 1000.0f);
        vmath::mat4 mv_matrix =
                vmath::translate(x_translate, y_translate, -4.0f) *
                vmath::rotate((float)currentTime * 45.0f, 0.0f, 1.0f, 0.0f) *
                vmath::rotate((float)currentTime * 81.0f, 1.0f, 0.0f, 0.0f);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
        glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Game::~Game() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();
}



