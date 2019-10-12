#pragma once

#include <GLFW/glfw3.h>
#include "GameControlState.h"
#include "PausedControlState.h"

class Window {
public:
    explicit Window();
    ~Window();

    void initialize();
    void ProcessGameControlState(GameControlState& controlState);
    void ProcessGamePausedState(PausedControlState& controlState);
    bool ShouldExit();
    void SwapBuffersAndPollEvents();

private:
    GLFWwindow* window;
};

