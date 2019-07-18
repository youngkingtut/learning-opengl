#include <iostream>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vmath.h>

#include "src/ShaderCompiler/ShaderCompiler.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LeraningOpenGL", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // triangle 1
    static const GLfloat vertices[] = {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            0.25f, -0.25f, -0.25f,

            0.25f, -0.25f, -0.25f,
            0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,

            0.25f, -0.25f, -0.25f,
            0.25f, -0.25f,  0.25f,
            0.25f,  0.25f, -0.25f,

            0.25f, -0.25f,  0.25f,
            0.25f,  0.25f,  0.25f,
            0.25f,  0.25f, -0.25f,

            0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
            0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            0.25f, -0.25f,  0.25f,
            0.25f, -0.25f, -0.25f,

            0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f,  0.25f,

            -0.25f,  0.25f, -0.25f,
            0.25f,  0.25f, -0.25f,
            0.25f,  0.25f,  0.25f,

            0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f, -0.25f
    };

    GLuint vao;
    GLuint vbo;

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    GLuint shaderProgram = LoadShaders("Shaders/shader.vert", "Shaders/shader.frag");
    GLint mv_location = glGetUniformLocation(shaderProgram, "mv_matrix");
    GLint proj_location = glGetUniformLocation(shaderProgram, "proj_matrix");

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    while (!glfwWindowShouldClose(window)) {
        float currentTime = 2 * (float)std::clock() / CLOCKS_PER_SEC;
        processInput(window);
        static const GLfloat one = 1.0f;

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearBufferfv(GL_DEPTH, 0, &one);


        float f = (float)currentTime * (float)M_PI * 0.1f;
        vmath::mat4 proj_matrix = vmath::perspective(50.0f, (float)8/6, 0.1f, 1000.0f);
        vmath::mat4 mv_matrix =
                vmath::translate(0.0f, 0.0f, -4.0f) *
                vmath::translate(sinf(2.1f * f) * 0.5f,
                                 cosf(1.7f * f) * 0.5f,
                                 sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) *
                vmath::rotate((float)currentTime * 45.0f, 0.0f, 1.0f, 0.0f) *
                vmath::rotate((float)currentTime * 81.0f, 1.0f, 0.0f, 0.0f);



        glUseProgram(shaderProgram);
        glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
        glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return 0;
}