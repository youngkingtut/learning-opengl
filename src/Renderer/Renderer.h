#pragma once

#include <map>

#include <glad/glad.h>

#include "../Utils/Random.h"
#include "../Game/World.h"
#include "Models/BaseModel.h"
#include "Models/PlayerModel.h"
#include "Models/ChaserEnemyModel.h"
#include "Models/WorldModel.h"
#include "Models/BulletModel.h"
#include "Models/SimpleEnemyModel.h"
#include "Texture.h"


// Text Rendering using this guide: https://learnopengl.com/In-Practice/Text-Rendering
struct Character {
    GLuint textureId;   // ID handle of the glyph texture
    glm::ivec2 size;    // Size of glyph
    glm::ivec2 bearing; // Offset from baseline to left/top of glyph
    GLuint offset;      // Horizontal offset to advance to next glyph
};


class Renderer {
public:
    explicit Renderer() = default;
    ~Renderer();

    void initialize();
    void renderWorld(const World& world);
    void renderGameOverScreen(const World& world);
    void renderGamePaused(const World& world);

private:
    // models
    WorldModel worldModel{};
    PlayerModel playerModel{};
    ChaserEnemyModel chaserEnemyModel{};
    SimpleEnemyModel simpleEnemyModel{};
    BulletModel bulletModel{};

    // shaders
    GLuint worldShaderProgram{0};
    GLuint textShaderProgram{0};
    GLuint starFieldProgram{0};

    // uniforms
    GLuint modelLocation{0};
    GLuint viewLocation{0};
    GLuint projectionLocation{0};
    GLuint colorLocation{0};
    GLuint uniformStarTime{0};
    GLuint uniformStarProjectionMatrix{0};
    GLuint uniformStarViewMatrix{0};

    // buffers
    GLuint textVAO{0};
    GLuint textVBO{0};
    GLuint starVAO{0};
    GLuint starBuffer{0};

    // textures
    Texture starTexture{};

    // stores
    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};
    std::map<GLchar, Character> characters{};

    void initializeText();
    void initializeStarField();
    void renderText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, const glm::vec3& color);
    void renderStarField(const glm::mat4& translatedViewMatrix);
    static void clearScreen();
};
