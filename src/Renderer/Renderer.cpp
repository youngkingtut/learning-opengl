#include <iostream>
#include <ctime>
#include <vmath.h>

#include "Renderer.h"

#include "../ShaderCompiler/ShaderCompiler.hpp"
#include "../Utils/Constants.h"


Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Renderer::initialize() {
    // todo calculate based on world size?
    float depth = -760.0f;


    static const GLfloat vertices[] = {
            // World
            -WORLD_SIZE_WIDTH,  WORLD_SIZE_HEIGHT, depth,
             WORLD_SIZE_WIDTH,  WORLD_SIZE_HEIGHT, depth,
             WORLD_SIZE_WIDTH, -WORLD_SIZE_HEIGHT, depth,
            -WORLD_SIZE_WIDTH, -WORLD_SIZE_HEIGHT, depth,

            // Player
            -PLAYER_SIZE_WIDTH,  -PLAYER_SIZE_HEIGHT, depth,
            PLAYER_SIZE_WIDTH,  -PLAYER_SIZE_HEIGHT, depth,
            0.0f,   PLAYER_SIZE_HEIGHT, depth,

            // Bullet
            -2.5, -2.5, depth,
            -2.5,  2.5, depth,
            2.5,  2.5, depth,
            2.5, -2.5, depth,

            // Enemy
            -5.0, -5.0, depth,
            -5.0,  5.0, depth,
            5.0,  5.0, depth,
            5.0, -5.0, depth,
    };

    static const GLuint indices[] = {
            // World
            0, 1, 2, 3, 0,

            // Player
            6, 5, 4,

            // Bullet
            7, 8, 9,
            9, 10, 7,

            // Enemy
            11, 12, 13,
            13, 14, 11,
    };


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shaderProgram = LoadShaders("Shaders/shader.vert", "Shaders/shader.frag");
    modelViewLocation = glGetUniformLocation(shaderProgram, "mv_matrix");
    projectionLocation = glGetUniformLocation(shaderProgram, "proj_matrix");

}

void Renderer::render(const World& world, float aspectRatio) {
    static const GLfloat one = 1.0f;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearBufferfv(GL_DEPTH, 0, &one);

    vmath::vec2 playerPosition = world.getPlayer().getPosition();
    float playerAngle = world.getPlayer().getAngle();

    vmath::mat4 projectionMatrix = vmath::perspective(WINDOW_FOV, aspectRatio, 0.1f, 1000.0f);


    glUseProgram(shaderProgram);

    // draw world
    glBindVertexArray(vao);
    vmath::mat4 modelViewMatrix = vmath::translate(0.0f, 0.0f, 0.0f);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix);
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);
    glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (GLvoid*)(0 * sizeof(GLuint)));

    // draw player
    modelViewMatrix = vmath::translate(playerPosition[0], playerPosition[1], 0.0f) *
                      vmath::rotate(playerAngle, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(5 * sizeof(GLuint)));


    // draw bullets
    for(auto & bullet : world.getBullets()) {
        vmath::vec2 bulletPosition = bullet.getPosition();
        modelViewMatrix = vmath::translate(bulletPosition[0], bulletPosition[1], 0.0f);
        glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(8 * sizeof(GLuint)));
    }

    // draw enemies
    for(auto & enemy : world.getEnemies()) {
        vmath::vec2 enemyPosition = enemy.getPosition();
        modelViewMatrix = vmath::translate(enemyPosition[0], enemyPosition[1], 0.0f) *
                          vmath::rotate(45.0f, 0.0f, 0.0f, 1.0f);
        glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(14 * sizeof(GLuint)));
    }

}
