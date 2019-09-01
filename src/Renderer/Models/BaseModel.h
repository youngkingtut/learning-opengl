#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ModelType.h"


class BaseModel {
public:
    virtual void loadStatic() = 0;
protected:
    GLuint vertexArrayObject{0};
    GLuint vertexBufferObject{0};
    GLuint elementBufferObject{0};
private:
    void loadFromFile(const char* filename, std::vector<glm::vec3> &vertices, std::vector<GLuint> &elements);
};
