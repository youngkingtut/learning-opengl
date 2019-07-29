#include <iostream>
#include <ctime>
#include <vmath.h>

#include "../ShaderCompiler/ShaderCompiler.hpp"
#include "Renderer.h"


Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Renderer::initialize() {
    vao = 0;
    vbo = 0;
    ebo = 0;

    // cube
    static const GLfloat vertices[] = {
            -0.25f,  0.0f, 0.0f,
             0.25f,  0.0f, 0.0f,
              0.0f,  0.5f, 0.0f,
    };

    static const GLuint indicies[] = {
            2, 1, 0
    };


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shaderProgram = LoadShaders("Shaders/shader.vert", "Shaders/shader.frag");
    mv_location = glGetUniformLocation(shaderProgram, "mv_matrix");
    proj_location = glGetUniformLocation(shaderProgram, "proj_matrix");
}

void Renderer::render(const World& world, float aspectRatio) {
    static const GLfloat one = 1.0f;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearBufferfv(GL_DEPTH, 0, &one);

    vmath::vec2 playerPosition = world.getPlayer().getPosition();
    float playerAngle = world.getPlayer().getAngle();

    vmath::mat4 proj_matrix = vmath::perspective(50.0f, aspectRatio, 0.1f, 1000.0f);
    vmath::mat4 mv_matrix =
            vmath::translate(playerPosition[0], playerPosition[1], -13.0f) *
            vmath::rotate(playerAngle, 0.0f, 0.0f, 1.0f);

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}
