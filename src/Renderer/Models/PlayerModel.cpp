#include "PlayerModel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void PlayerModel::loadStatic() {
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> elements;

    loadFromFile("Resources/Models/player.obj", vertices, elements);
    elementBufferSize = elements.size();

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

void PlayerModel::draw(const Player &player, const GLuint& modelViewMatrixLocation, const GLuint& colorLocation) {
    glBindVertexArray(vertexArrayObject);
    glm::vec2 playerPosition = player.getPosition();
    float playerAngle = player.getAngle();
    glm::mat4 modelViewMatrix = glm::translate(glm::mat4(), glm::vec3(playerPosition[0], playerPosition[1], 0.0F)) *
                                glm::rotate(glm::mat4(), playerAngle, glm::vec3(0.0F, 0.0F, 1.0F));
    glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glUniform4f(colorLocation, color.r, color.g, color.b, color.a);
    glDrawElements(GL_TRIANGLES, elementBufferSize, GL_UNSIGNED_INT, nullptr);
}
