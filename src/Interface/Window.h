#pragma once

#include <GLFW/glfw3.h>
#include "../Utils/ConfigStore.h"
#include "ControlState.h"

class Window {
public:
    explicit Window(ConfigStore c);
    ~Window();

    void initialize();
    void ProcessInput(ControlState& controlState);
    bool ShouldExit();
    void SwapBuffersAndPollEvents();
    float GetAspectRatio();

private:
    ConfigStore config;
    GLFWwindow* window;

    static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

