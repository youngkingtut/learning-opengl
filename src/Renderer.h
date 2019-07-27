#pragma once

#include <glad/glad.h>

class Renderer {
public:
    ~Renderer();

    void initialize();
    void render(float aspectRatio);

private:
    GLuint shaderProgram;
    GLint mv_location;
    GLint proj_location;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
};

