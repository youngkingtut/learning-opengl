#include <iostream>
#include <ctime>
#include <vmath.h>

#include "../ShaderCompiler/ShaderCompiler.hpp"
#include "Renderer.h"


Renderer::~Renderer() {
    glDeleteVertexArrays(3, vao);
    glDeleteBuffers(3, vbo);
    glDeleteBuffers(3, ebo);
}

void Renderer::initialize(const World& world) {
    vmath::vec2 worldSize = world.getSize();
    vmath::vec2 playerSize = world.getPlayer().getSize();

    // todo calculate based on world size?
    float depth = -760.0f;

    static const GLfloat bulletVertices[] = {
            -2.5, -2.5, depth,
            -2.5,  2.5, depth,
             2.5,  2.5, depth,
             2.5, -2.5, depth,
    };

    static const GLfloat playerVertices[] = {
            -playerSize[0]/2,  -playerSize[1]/2, depth,
             playerSize[0]/2,  -playerSize[1]/2, depth,
              0.0f,   playerSize[1]/2, depth,
    };

    static const GLfloat worldVertices[] = {
            -worldSize[0],  worldSize[1], depth,
             worldSize[0],  worldSize[1], depth,
             worldSize[0], -worldSize[1], depth,
            -worldSize[0], -worldSize[1], depth,
    };

    static const GLuint playerIndices[] = {
            2, 1, 0,
    };

    static const GLuint worldIndices[] = {
            0, 1, 2, 3, 0,
    };

    static const GLuint bulletIndices[] = {
            0, 1, 2,
            2, 3, 0,
    };


    glGenVertexArrays(3, vao);
    glGenBuffers(3, vbo);
    glGenBuffers(3, ebo);

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

    glBindVertexArray(vao[2]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bulletVertices), bulletVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bulletIndices), bulletIndices, GL_STATIC_DRAW);

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

    vmath::mat4 projectionMatrix = vmath::perspective(50.0f, aspectRatio, 0.1f, 1000.0f);


    glUseProgram(shaderProgram);

    // draw world
    glBindVertexArray(vao[1]);
    vmath::mat4 modelViewMatrix = vmath::translate(0.0f, 0.0f, 0.0f);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, projectionMatrix);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, modelViewMatrix);
    glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, nullptr);

    // draw player
    glBindVertexArray(vao[0]);
    modelViewMatrix = vmath::translate(playerPosition[0], playerPosition[1], 0.0f) *
                      vmath::rotate(playerAngle, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, modelViewMatrix);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);


    // draw bullets
    glBindVertexArray(vao[2]);

    for(auto & bullet : world.getBullets()) {
        vmath::vec2 bulletPosition = bullet.getPosition();
        float bulletAngle = bullet.getAngle();
        modelViewMatrix = vmath::translate(bulletPosition[0], bulletPosition[1], 0.0f) *
                          vmath::rotate(bulletAngle, 0.0f, 0.0f, 1.0f);
        glUniformMatrix4fv(mv_location, 1, GL_FALSE, modelViewMatrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

}
