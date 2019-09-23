#pragma once

#include <glad/glad.h>
#include "../../Game/Objects/Bullet.h"
#include "BaseModel.h"


class BulletModel : public BaseModel {
public:
    void loadStatic() override;
    void draw(const Bullet &bullet, const GLuint& modelViewMatrixLocation, const GLuint& colorLocation);
private:
    glm::vec4 color = glm::vec4(1.0F, 0.0F, 1.0F, 1.0F);
};
