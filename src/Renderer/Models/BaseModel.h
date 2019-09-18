#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>


class BaseModel {
public:
    virtual void loadStatic() = 0;
    ~BaseModel();
protected:
    GLuint vertexArrayObject{0};
    GLuint vertexBufferObject{0};
    GLuint elementBufferObject{0};
    GLuint elementBufferSize{0};

    static void loadFromFile(const char* filename, std::vector<glm::vec3> &vertices, std::vector<GLuint> &elements);
};
