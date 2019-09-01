#pragma once

#include <glad/glad.h>
#include "../../Game/Objects/Enemy.h"
#include "BaseModel.h"


class WorldModel : public BaseModel {
public:
    void loadStatic() override;
    void draw(const GLuint &modelViewMatrixLocation);
};
