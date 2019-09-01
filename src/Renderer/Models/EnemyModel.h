#pragma once

#include <glad/glad.h>
#include "../../Game/Objects/Enemy.h"
#include "BaseModel.h"


class EnemyModel : public BaseModel {
public:
    void loadStatic() override;
    void draw(const Enemy &enemy, const GLuint &modelViewMatrixLocation);
};
