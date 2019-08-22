#include <iostream>
#include <ctime>
#include <map>

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
    glDeleteVertexArrays(1, &worldVAO);
    glDeleteBuffers(1, &worldVBO);
    glDeleteBuffers(1, &worldEBO);
    glDeleteVertexArrays(1, &textVAO);
    glDeleteBuffers(1, &textVBO);
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
            -PLAYER_SIZE,  -PLAYER_SIZE, depth,
            PLAYER_SIZE,  -PLAYER_SIZE, depth,
            0.0f,   PLAYER_SIZE, depth,

            // Bullet
            -BULLET_SIZE, -BULLET_SIZE, depth,
            -BULLET_SIZE,  BULLET_SIZE, depth,
            BULLET_SIZE,  BULLET_SIZE, depth,
            BULLET_SIZE, -BULLET_SIZE, depth,

            // Enemy
            -ENEMY_SIZE, -ENEMY_SIZE, depth,
            -ENEMY_SIZE,  ENEMY_SIZE, depth,
            ENEMY_SIZE,  ENEMY_SIZE, depth,
            ENEMY_SIZE, -ENEMY_SIZE, depth,
    };

    static const GLuint indices[] = {
            // World
            0, 1, 2, 3, 0,

            // Player
            4, 5, 6,

            // Bullet
            9, 8, 7,
            7, 10, 9,

            // Enemy
            13, 12, 11,
            11, 14, 13,
    };


    glGenVertexArrays(1, &worldVAO);
    glGenBuffers(1, &worldVBO);
    glGenBuffers(1, &worldEBO);

    glBindVertexArray(worldVAO);

    glBindBuffer(GL_ARRAY_BUFFER, worldVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, worldEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    worldShaderProgram = LoadShaders("Resources/Shaders/shader.vert", "Resources/Shaders/shader.frag");
    modelViewLocation = glGetUniformLocation(worldShaderProgram, "mv_matrix");
    projectionLocation = glGetUniformLocation(worldShaderProgram, "proj_matrix");
    projectionMatrix = glm::perspective(FOV, WINDOW_ASPECT_RATIO, 0.1f, 800.0f);

    // Set OpenGL options
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Compile and setup the shader
    textShaderProgram = LoadShaders("Resources/Shaders/text.vert", "Resources/Shaders/text.frag");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WINDOW_SIZE_WIDTH), 0.0f, static_cast<GLfloat>(WINDOW_SIZE_HEIGHT));
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

void Renderer::renderWorld(const World &world) {
    static const GLfloat one = 1.0f;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glUseProgram(worldShaderProgram);
    glBindVertexArray(worldVAO);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // draw world
    glm::mat4 modelViewMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (GLvoid*)(0 * sizeof(GLuint)));

    // draw player
    glm::vec2 playerPosition = world.getPlayer().getPosition();
    float playerAngle = world.getPlayer().getAngle();
    modelViewMatrix = glm::translate(glm::mat4(), glm::vec3(playerPosition[0], playerPosition[1], 0.0f)) *
                      glm::rotate(glm::mat4(), playerAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(5 * sizeof(GLuint)));


    // draw bullets
    for(auto & bullet : world.getBullets()) {
        glm::vec2 bulletPosition = bullet.getPosition();
        float bulletAngle = bullet.getAngle();
        modelViewMatrix = glm::translate(glm::mat4(), glm::vec3(bulletPosition[0], bulletPosition[1], 0.0f)) *
                          glm::rotate(glm::mat4(), bulletAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(8 * sizeof(GLuint)));
    }

    // draw enemies
    for(auto & enemy : world.getEnemies()) {
        glm::vec2 enemyPosition = enemy.getPosition();
        modelViewMatrix = glm::translate(glm::mat4(), glm::vec3(enemyPosition[0], enemyPosition[1], 0.0f));
        glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(14 * sizeof(GLuint)));
    }

    glUseProgram(textShaderProgram);
    std::stringstream ss;
    ss << "Score " << world.getState().score;
    renderText(ss.str(), 45.0f, WINDOW_SIZE_HEIGHT - 33.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    glBindVertexArray(0);
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

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}
