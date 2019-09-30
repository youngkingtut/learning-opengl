#pragma once

#include <glad/glad.h>
#include "../../Game/Objects/ChaserEnemy.h"
#include "BaseModel.h"


class ChaserEnemyModel : public BaseModel {
public:
    void loadStatic() override;
    void draw(const ChaserEnemy &enemy, const GLuint& modelViewMatrixLocation, const GLuint& colorLocation);
private:
    glm::vec4 color = glm::vec4(0.0F, 1.0F, 1.0F, 1.0F);
};
