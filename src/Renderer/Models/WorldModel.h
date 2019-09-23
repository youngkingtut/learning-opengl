#pragma once

#include <glad/glad.h>
#include "../../Game/Objects/Enemy.h"
#include "BaseModel.h"


class WorldModel : public BaseModel {
public:
    void loadStatic() override;
    void draw(const GLuint& modelViewMatrixLocation, const GLuint& colorLocation);

private:
    glm::vec4 color = glm::vec4(1.0F, 1.0F, 1.0F, 0.3F);
};
