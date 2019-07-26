#pragma once

#include <GLFW/glfw3.h>
#include "ConfigStore.h"

class Window {
public:
    ~Window();

    void initialize(ConfigStore config);
    void ProcessInput();
    bool ShouldExit();
    void SwapBuffersAndPollEvents();

private:
    GLFWwindow* window;
    static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

