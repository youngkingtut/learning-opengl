#include <iostream>
#include <ctime>
#include <vmath.h>

#include "../ShaderCompiler/ShaderCompiler.hpp"
#include "Renderer.h"


Renderer::~Renderer() {
    glDeleteVertexArrays(2, vao);
    glDeleteBuffers(2, vbo);
    glDeleteBuffers(2, ebo);
}

void Renderer::initialize(const World& world) {
    vmath::vec2 worldSize = world.getSize();
    vmath::vec2 playerSize = world.getPlayer().getSize();

    static const GLfloat playerVertices[] = {
            -playerSize[0]/2,  0.0f, 0.0f,
             playerSize[0]/2,  0.0f, 0.0f,
              0.0f,  playerSize[1], 0.0f,
    };

    static const GLfloat worldVertices[] = {
            -worldSize[0],  worldSize[1], 0.0f,
             worldSize[0],  worldSize[1], 0.0f,
             worldSize[0], -worldSize[1], 0.0f,
            -worldSize[0], -worldSize[1], 0.0f,
    };

    static const GLuint playerIndices[] = {
            2, 1, 0,
    };

    static const GLuint worldIndices[] = {
            0, 1, 2, 3, 0,
    };


    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);
    glGenBuffers(2, ebo);

    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(playerVertices), playerVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(playerIndices), playerIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(vao[1]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(worldVertices), worldVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(worldIndices), worldIndices, GL_STATIC_DRAW);

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
            vmath::translate(playerPosition[0], playerPosition[1], -760.0f) *
            vmath::rotate(playerAngle, 0.0f, 0.0f, 1.0f);

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
    glBindVertexArray(vao[0]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

    mv_matrix = vmath::translate(0.0f, 0.0f, -760.0f);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);


    glBindVertexArray(vao[1]);
    glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, nullptr);
}
