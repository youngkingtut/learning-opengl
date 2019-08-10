#pragma once

#include <GLFW/glfw3.h>
#include "ControlState.h"

class Window {
public:
    explicit Window();
    ~Window();

    void initialize();
    void ProcessInput(ControlState& controlState);
    bool ShouldExit();
    void SwapBuffersAndPollEvents();
    float GetAspectRatio();

private:
    GLFWwindow* window;
};

