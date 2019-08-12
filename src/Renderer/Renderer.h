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
    GLuint shaderProgram{0};
    GLint modelViewLocation{0};
    GLint projectionLocation{0};
    GLuint vao{0};
    GLuint vbo{0};
    GLuint ebo{0};
};

