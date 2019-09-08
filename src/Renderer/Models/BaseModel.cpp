#include "BaseModel.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <glm/geometric.hpp>
#include <stdlib.h>


BaseModel::~BaseModel() {
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);
}

void BaseModel::loadFromFile(const char *filename, std::vector<glm::vec3> &vertices, std::vector<GLuint> &elements) {
    std::ifstream in(filename, std::ios::in);
    if(!in.is_open()) {
        std::cout << "Cannot open " << filename << std::endl;
        exit(-1);
    }

    std::string line;
    while (getline(in, line)) {
        if (line.substr(0,2) == "v ") {
            std::istringstream s(line.substr(2));
            glm::vec3 v;
            s >> v.x;
            s >> v.y;
            s >> v.z;
            vertices.push_back(v);
        } else if (line.substr(0,2) == "f ") {
            std::istringstream s(line.substr(2));
            GLuint a;
            GLuint b;
            GLuint c;
            s >> a;
            s >> b;
            s >> c;
            a--;
            b--;
            c--;
            elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
    }
}
