#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <stb_image.h>

class Texture {
public:
    Texture() = default;
    explicit Texture(std::string fileLocation);
    ~Texture();

    bool LoadTexture();
    bool LoadTextureA();

    void UseTexture() const;
    void ClearTexture();

private:
    GLuint textureID{0};
    int width{0};
    int height{0};
    int bitDepth{0};

    std::string fileLocation;
};
