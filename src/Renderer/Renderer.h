#pragma once

#include <glad/glad.h>

#include "../Game/World.h"


class Renderer {
public:
    ~Renderer();

    void initialize(const World& world);
    void render(const World& world, float aspectRatio);

private:
    GLuint shaderProgram{};
    GLint mv_location{};
    GLint proj_location{};
    GLuint vao[2]{0, 0};
    GLuint vbo[2]{0, 0};
    GLuint ebo[2]{0, 0};
};

