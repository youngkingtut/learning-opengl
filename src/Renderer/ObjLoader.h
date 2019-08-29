#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glad/glad.h>


void loadObj(const char* filename, std::vector<glm::vec3> &vertices, std::vector<GLuint> &elements);
