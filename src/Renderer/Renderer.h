#pragma once

#include <glad/glad.h>

#include "../Game/World.h"


class Renderer {
public:
    explicit Renderer() = default;
    ~Renderer();

    void initialize();
    void render(const World& world, float aspectRatio);

private:
    GLuint shaderProgram{};
    GLint modelViewLocation{};
    GLint projectionLocation{};
    GLuint vao[3]{0, 0, 0};
    GLuint vbo[3]{0, 0, 0};
    GLuint ebo[3]{0, 0, 0};
};

