#include "Window.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

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
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
    glfwWindowHint(GLFW_CENTER_CURSOR, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GAME_TITLE, nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::exception();
    }

    glfwMakeContextCurrent(window);

    // Load Icon for Window
    GLFWimage image;
    image.pixels = stbi_load("Resources/Icons/32x32.png", &image.width, &image.height, nullptr, 0);
    glfwSetWindowIcon(window, 1, &image);
    stbi_image_free(image.pixels);

    // Must initialize Glad after
    // https://www.glfw.org/docs/latest/quick.html#quick_context_current
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // todo create exceptions
        throw std::exception();
    }

    // Hiding cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Trying sticky keys for event based processing with the keyboard
    // https://www.glfw.org/docs/latest/input_guide.html#input_key
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
}

void Window::ProcessGameOverState(GameOverControlState &controlState) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        controlState.setReset(true);
    }
}

void Window::ProcessGamePausedState(PausedControlState &controlState) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    int pKeyStatus = glfwGetKey(window, GLFW_KEY_P);
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        controlState.setPausePress(true);
        controlState.setPauseRelease(false);
    } else if(pKeyStatus == GLFW_RELEASE) {
        controlState.setPauseRelease(controlState.getPausePress());
        controlState.setPausePress(false);
    }
}

void Window::ProcessGameControlState(GameControlState& controlState) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    int pKeyStatus = glfwGetKey(window, GLFW_KEY_P);
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        controlState.setPausePress(true);
        controlState.setPauseRelease(false);
    } else if(pKeyStatus == GLFW_RELEASE) {
        controlState.setPauseRelease(controlState.getPausePress());
        controlState.setPausePress(false);
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
        if (glm::abs(movementXAxis) < JOYSTICK_DEAD_ZONE_LOWER && glm::abs(movementYAxis) < JOYSTICK_DEAD_ZONE_LOWER) {
            xMovement = 0.0F;
            yMovement = 0.0F;
        }
        controlState.setMovementDirection(xMovement, yMovement);

        if(bulletXAxis <  JOYSTICK_DEAD_ZONE_LOWER &&
           bulletXAxis > -JOYSTICK_DEAD_ZONE_LOWER &&
           bulletYAxis <  JOYSTICK_DEAD_ZONE_LOWER &&
           bulletYAxis > -JOYSTICK_DEAD_ZONE_LOWER) {
            controlState.setBulletDirection(0.0F, 0.0F);
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


        float x = 0.0F;
        float y = 0.0F;

        if(d_state == GLFW_PRESS && a_state != GLFW_PRESS) {
            x = 1.0F;
        }
        if(a_state == GLFW_PRESS && d_state != GLFW_PRESS) {
            x = -1.0F;
        }

        if(w_state == GLFW_PRESS && s_state != GLFW_PRESS) {
            y = -1.0F;
        }
        if(s_state == GLFW_PRESS && w_state != GLFW_PRESS) {
            y = 1.0F;
        }

        controlState.setMovementDirection(x, y);

        x = 0.0F;
        y = 0.0F;

        if(right_state == GLFW_PRESS && left_state != GLFW_PRESS) {
            x = 1.0F;
        }
        if(left_state == GLFW_PRESS && right_state != GLFW_PRESS) {
            x = -1.0F;
        }

        if(up_state == GLFW_PRESS && down_state != GLFW_PRESS) {
            y = 1.0F;
        }
        if(down_state == GLFW_PRESS && up_state != GLFW_PRESS) {
            y = -1.0F;
        }

        controlState.setBulletDirection(x, y);
    }
}

bool Window::ShouldExit() {
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffersAndPollEvents() {
    glFlush();
    glfwSwapInterval(0);
    glfwSwapBuffers(window);
    glfwPollEvents();
}
