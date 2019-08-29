#pragma once

#include <map>

#include <glad/glad.h>

#include "../Game/World.h"

// Text Rendering using this guide: https://learnopengl.com/In-Practice/Text-Rendering
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Renderer {
public:
    explicit Renderer() = default;
    ~Renderer();

    void initialize();
    void renderWorld(const World &world);
    void renderGameOverScreen();

private:
    GLuint worldShaderProgram{0};
    GLuint textShaderProgram{0};
    GLint modelViewLocation{0};
    GLint projectionLocation{0};
    GLuint worldVAO{0};
    GLuint worldVBO{0};
    GLuint worldEBO{0};
    GLuint textVAO{0};
    GLuint textVBO{0};
    glm::mat4 projectionMatrix{};
    std::map<GLchar, Character> characters{};

    GLuint worldOffset{0};
    GLuint playerOffset{0};
    GLuint enemyOffset{0};
    GLuint bulletOffset{0};

    void renderText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, const glm::vec3& color);
    static void clearScreen();
};

