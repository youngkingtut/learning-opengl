#include "WorldModel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Utils/Constants.h"


void WorldModel::loadStatic() {
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> elements;

    vertices.emplace_back(glm::vec3(-WORLD_SIZE_WIDTH,  WORLD_SIZE_HEIGHT, 0.0f));
    vertices.emplace_back(glm::vec3( WORLD_SIZE_WIDTH,  WORLD_SIZE_HEIGHT, 0.0f));
    vertices.emplace_back(glm::vec3( WORLD_SIZE_WIDTH, -WORLD_SIZE_HEIGHT, 0.0f));
    vertices.emplace_back(glm::vec3(-WORLD_SIZE_WIDTH, -WORLD_SIZE_HEIGHT, 0.0f));

    elements.emplace_back(0);
    elements.emplace_back(1);
    elements.emplace_back(2);
    elements.emplace_back(3);
    elements.emplace_back(0);

    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &elementBufferObject);

    glBindVertexArray(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), &elements[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
}

void WorldModel::draw(const GLuint &modelViewMatrixLocation) {
    glBindVertexArray(vertexArrayObject);
    glm::mat4 modelViewMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)) *
                                glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, nullptr);
}
