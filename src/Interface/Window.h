#pragma once

#include <GLFW/glfw3.h>
#include "GameControlState.h"
#include "PausedControlState.h"
#include "GameOverControlState.h"

class Window {
public:
    explicit Window();
    ~Window();

    void initialize();
    void ProcessGameControlState(GameControlState& controlState);
    void ProcessGamePausedState(PausedControlState& controlState);
    void ProcessGameOverState(GameOverControlState& controlState);
    bool ShouldExit();
    void SwapBuffersAndPollEvents();

private:
    GLFWwindow* window;
    double aspectRatio;
    double scale;
};

