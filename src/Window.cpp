#include "Window.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>


Window::~Window() {
    glfwTerminate();
}

/*
 * Callbacks
 */
void Window::FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}


void Window::initialize(ConfigStore config) {
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
        throw std::exception();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // todo create exceptions
        throw std::exception();
    }

    glfwSetFramebufferSizeCallback(window, Window::FrameBufferSizeCallback);
}



void Window::ProcessInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

bool Window::ShouldExit() {
    return !glfwWindowShouldClose(window);
}

void Window::SwapBuffersAndPollEvents() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
