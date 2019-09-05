#include "Window.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "../Utils/Constants.h"


Window::Window() :
    window(){}

Window::~Window() {
    glfwTerminate();
}


void Window::initialize() {
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
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GAME_TITLE, nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::exception();
    }

    glfwMakeContextCurrent(window);

    // Must initialize Glad after
    // https://www.glfw.org/docs/latest/quick.html#quick_context_current
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // todo create exceptions
        throw std::exception();
    }

    // Trying sticky keys for event based processing with the keyboard
    // https://www.glfw.org/docs/latest/input_guide.html#input_key
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void Window::ProcessInput(ControlState& controlState) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    if(present > 0) {
        int count;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
        float movementXAxis = axes[0];
        float movementYAxis = axes[1];
        float bulletXAxis = axes[2];
        float bulletYAxis = axes[3];

        // Account for dead zone to prevent drift from stationary stick
        float xMovement = movementXAxis;
        float yMovement = movementYAxis;
        if(glm::abs(movementXAxis) > JOYSTICK_DEAD_ZONE_UPPER) {
            if(movementXAxis > 0.0f) {
                xMovement = 1.0f;
            } else {
                xMovement = -1.0f;
            }
        } else if (glm::abs(movementXAxis) < JOYSTICK_DEAD_ZONE_LOWER) {
            xMovement = 0.0f;
        }
        if(glm::abs(movementYAxis) > JOYSTICK_DEAD_ZONE_UPPER) {
            if(movementYAxis > 0.0f) {
                yMovement = 1.0f;
            } else {
                yMovement = -1.0f;
            }
        } else if (glm::abs(movementYAxis) < JOYSTICK_DEAD_ZONE_LOWER) {
            yMovement = 0.0f;
        }
        controlState.setMovementDirection(xMovement, yMovement);

        if(bulletXAxis <  JOYSTICK_DEAD_ZONE_LOWER &&
           bulletXAxis > -JOYSTICK_DEAD_ZONE_LOWER &&
           bulletYAxis <  JOYSTICK_DEAD_ZONE_LOWER &&
           bulletYAxis > -JOYSTICK_DEAD_ZONE_LOWER) {
            controlState.setBulletDirection(0.0f, 0.0f);
        } else {
            controlState.setBulletDirection(bulletXAxis, -bulletYAxis);
        }
    } else {
        int w_state = glfwGetKey(window, GLFW_KEY_W);
        int a_state = glfwGetKey(window, GLFW_KEY_A);
        int s_state = glfwGetKey(window, GLFW_KEY_S);
        int d_state = glfwGetKey(window, GLFW_KEY_D);
        int up_state = glfwGetKey(window, GLFW_KEY_UP);
        int down_state = glfwGetKey(window, GLFW_KEY_DOWN);
        int left_state = glfwGetKey(window, GLFW_KEY_LEFT);
        int right_state = glfwGetKey(window, GLFW_KEY_RIGHT);


        float x = 0.0f;
        float y = 0.0f;

        if(d_state == GLFW_PRESS && a_state != GLFW_PRESS) {
            x = 1.0f;
        }
        if(a_state == GLFW_PRESS && d_state != GLFW_PRESS) {
            x = -1.0f;
        }

        if(w_state == GLFW_PRESS && s_state != GLFW_PRESS) {
            y = -1.0f;
        }
        if(s_state == GLFW_PRESS && w_state != GLFW_PRESS) {
            y = 1.0f;
        }

        controlState.setMovementDirection(x, y);

        x = 0.0f;
        y = 0.0f;

        if(right_state == GLFW_PRESS && left_state != GLFW_PRESS) {
            x = 1.0f;
        }
        if(left_state == GLFW_PRESS && right_state != GLFW_PRESS) {
            x = -1.0f;
        }

        if(up_state == GLFW_PRESS && down_state != GLFW_PRESS) {
            y = 1.0f;
        }
        if(down_state == GLFW_PRESS && up_state != GLFW_PRESS) {
            y = -1.0f;
        }

        controlState.setBulletDirection(x, y);
    }
}

bool Window::ShouldExit() {
    return !glfwWindowShouldClose(window);
}

void Window::SwapBuffersAndPollEvents() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
