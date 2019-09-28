#pragma once

#include <glad/glad.h>
#include "../../Game/Objects/SimpleEnemy.h"
#include "BaseModel.h"


class SimpleEnemyModel : public BaseModel {
public:
    void loadStatic() override;
    void draw(const SimpleEnemy &enemy, const GLuint& modelViewMatrixLocation, const GLuint& colorLocation);
private:
    glm::vec4 color = glm::vec4(0.0F, 1.0F, 1.0F, 1.0F);
};
