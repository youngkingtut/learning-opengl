#include <iostream>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include <sstream>
#include FT_FREETYPE_H

#include "Renderer.h"

#include "../ShaderCompiler/ShaderCompiler.hpp"
#include "../Utils/Constants.h"


Renderer::~Renderer() {
    glDeleteVertexArrays(1, &textVAO);
    glDeleteBuffers(1, &textVBO);
}


void Renderer::initialize() {
    // Set OpenGL options
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Load Models
    worldModel.loadStatic();
    playerModel.loadStatic();
    chaserEnemyModel.loadStatic();
    simpleEnemyModel.loadStatic();
    bulletModel.loadStatic();

    // Initialize World Shader
    worldShaderProgram = LoadShaders("Resources/Shaders/shader.vert", "Resources/Shaders/shader.frag");
    modelLocation = glGetUniformLocation(worldShaderProgram, MODEL_MATRIX);
    viewLocation = glGetUniformLocation(worldShaderProgram, VIEW_MATRIX);
    colorLocation = glGetUniformLocation(worldShaderProgram, OBJECT_COLOR);
    viewMatrix = glm::lookAt(glm::vec3(0.0F, 0.0F, 150.0F), glm::vec3(0.0F, 0.0F, -1.0F), glm::vec3(0.0F, 1.0F, 0.0F));
    projectionLocation = glGetUniformLocation(worldShaderProgram, PROJECTION_MATRIX);
    projectionMatrix = glm::perspective(FOV, WINDOW_ASPECT_RATIO, 0.1F, 200.0F);

    // Initialize Text
    initializeText();
}


void Renderer::renderWorld(const World &world) {
    clearScreen();

    Player player = world.getPlayer();
    glm::vec2 playerPosition = player.getPosition();

    // Translate everything in the opposite direction of the player and bound it
    float translateX = -playerPosition[0];
    float translateY = -playerPosition[1];
    if(translateX > CAMERA_MAX_TRUCK || translateX < -CAMERA_MAX_TRUCK) {
        translateX = (translateX > 0 ? CAMERA_MAX_TRUCK : -CAMERA_MAX_TRUCK);
    }
    if(translateY > CAMERA_MAX_PEDESTAL || translateY < -CAMERA_MAX_PEDESTAL) {
        translateY = (translateY > 0 ? CAMERA_MAX_PEDESTAL : -CAMERA_MAX_PEDESTAL);
    }
    glm::mat4 translatedViewMatrix = glm::translate(viewMatrix, glm::vec3(translateX, translateY, 0.0F));

    glUseProgram(worldShaderProgram);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(translatedViewMatrix));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // draw world
    worldModel.draw(modelLocation, colorLocation);

    // draw player
    playerModel.draw(player, modelLocation, colorLocation);

    // draw bullets
    for(auto & bullet : world.getBullets()) {
        bulletModel.draw(bullet, modelLocation, colorLocation);
    }

    // draw enemies
    for(auto & enemy : world.getMoverEnemies()) {
        chaserEnemyModel.draw(enemy, modelLocation, colorLocation);
    }
    for(auto& enemy : world.getSimpleEnemies()) {
        simpleEnemyModel.draw(enemy, modelLocation, colorLocation);
    }

    glUseProgram(textShaderProgram);
    std::stringstream score;
    std::stringstream lives;
    score << "Score " << world.getState().score;
    lives << "Lives " << world.getState().lives;
    renderText(score.str(), 45.0F, WINDOW_SIZE_HEIGHT - 33.0F, 1.0F, glm::vec3(0.2F, 1.0F, 1.0F));
    renderText(lives.str(), WINDOW_SIZE_WIDTH - 200.0F, WINDOW_SIZE_HEIGHT - 33.0F, 1.0F, glm::vec3(1.0F, 1.0F, 1.0F));
}


void Renderer::renderGameOverScreen(const World& world) {
    clearScreen();

    glUseProgram(worldShaderProgram);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // draw world
    worldModel.draw(modelLocation, colorLocation);

    glUseProgram(textShaderProgram);
    std::string gameOver = "GAME OVER";
    std::stringstream score;
    std::stringstream lives;
    score << "Score " << world.getState().score;
    lives << "Lives " << world.getState().lives;
    renderText(score.str(), 45.0F, WINDOW_SIZE_HEIGHT - 33.0F, 1.0F, glm::vec3(1.0F, 1.0F, 1.0F));
    renderText(lives.str(), WINDOW_SIZE_WIDTH - 200.0F, WINDOW_SIZE_HEIGHT - 33.0F, 1.0F, glm::vec3(1.0F, 1.0F, 1.0F));
    renderText(gameOver, 210.0F, WINDOW_SIZE_HEIGHT - 310.0F, 2.0F, glm::vec3(1.0F, 1.0F, 1.0F));
}

void Renderer::renderGamePaused(const World &world) {
    clearScreen();

    Player player = world.getPlayer();
    glm::vec2 playerPosition = player.getPosition();

    // Translate everything in the opposite direction of the player and bound it
    float translateX = -playerPosition[0];
    float translateY = -playerPosition[1];
    if(translateX > CAMERA_MAX_TRUCK || translateX < -CAMERA_MAX_TRUCK) {
        translateX = (translateX > 0 ? CAMERA_MAX_TRUCK : -CAMERA_MAX_TRUCK);
    }
    if(translateY > CAMERA_MAX_PEDESTAL || translateY < -CAMERA_MAX_PEDESTAL) {
        translateY = (translateY > 0 ? CAMERA_MAX_PEDESTAL : -CAMERA_MAX_PEDESTAL);
    }
    glm::mat4 translatedViewMatrix = glm::translate(viewMatrix, glm::vec3(translateX, translateY, 0.0F));

    glUseProgram(worldShaderProgram);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(translatedViewMatrix));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // draw world
    worldModel.draw(modelLocation, colorLocation);

    glUseProgram(textShaderProgram);
    std::string paused = "Paused";
    std::stringstream score;
    std::stringstream lives;
    score << "Score " << world.getState().score;
    lives << "Lives " << world.getState().lives;
    renderText(score.str(), 45.0F, WINDOW_SIZE_HEIGHT - 33.0F, 1.0F, glm::vec3(0.2F, 1.0F, 1.0F));
    renderText(lives.str(), WINDOW_SIZE_WIDTH - 200.0F, WINDOW_SIZE_HEIGHT - 33.0F, 1.0F, glm::vec3(1.0F, 1.0F, 1.0F));
    renderText(paused, 250.0F, WINDOW_SIZE_HEIGHT - 310.0F, 2.0F, glm::vec3(1.0F, 1.0F, 1.0F));
}

void Renderer::renderText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, const glm::vec3& color) {
    // Activate corresponding render state
    glUniform3f(glGetUniformLocation(textShaderProgram, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characters[*c];

        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y - static_cast<float>(ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;
        // Update VBO for each character
        std::array<std::array<GLfloat, 4>, 6> vertices = {{
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        }};
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureId);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data()); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.offset >> 6) * scale; // Bit shift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::clearScreen() {
    glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
    glClearDepthf(1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::initializeText() {
    // Compile and setup the shader
    textShaderProgram = LoadShaders("Resources/Shaders/text.vert", "Resources/Shaders/text.frag");
    glm::mat4 projection = glm::ortho(0.0F, static_cast<GLfloat>(WINDOW_SIZE_WIDTH), 0.0F, static_cast<GLfloat>(WINDOW_SIZE_HEIGHT));
    glUseProgram(textShaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(textShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        exit(-1);
    }

    // Load font as face
    FT_Face face;
    if (FT_New_Face(ft, "Resources/Fonts/joystix_monospace.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        exit(-1);
    }

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 24);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (unsigned int)face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
