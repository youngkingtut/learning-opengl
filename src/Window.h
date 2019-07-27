#pragma once

#include <GLFW/glfw3.h>
#include "ConfigStore.h"
#include "ControlState.h"

class Window {
public:
    ~Window();

    void initialize(ConfigStore config);
    void ProcessInput(ControlState& controlState);
    bool ShouldExit();
    void SwapBuffersAndPollEvents();
    float GetAspectRatio();

private:
    GLFWwindow* window;
    static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

