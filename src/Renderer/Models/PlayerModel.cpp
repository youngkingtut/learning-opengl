#include "PlayerModel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Utils/Constants.h"


void PlayerModel::loadStatic() {
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> elements;

    vertices.emplace_back(glm::vec3(-PLAYER_SIZE,  -PLAYER_SIZE, -760.0f));
    vertices.emplace_back(glm::vec3( PLAYER_SIZE,  -PLAYER_SIZE, -760.0f));
    vertices.emplace_back(glm::vec3(        0.0f,   PLAYER_SIZE, -760.0f));

    elements.emplace_back(0);
    elements.emplace_back(1);
    elements.emplace_back(2);

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

    glBindVertexArray(0);
}

void PlayerModel::draw(const Player &player, const GLuint &modelViewMatrixLocation) {
    glBindVertexArray(vertexArrayObject);
    glm::vec2 playerPosition = player.getPosition();
    float playerAngle = player.getAngle();
    glm::mat4 modelViewMatrix = glm::translate(glm::mat4(), glm::vec3(playerPosition[0], playerPosition[1], 0.0f)) *
                                glm::rotate(glm::mat4(), playerAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}