#pragma once

#include <glad/glad.h>
#include "../../Game/Objects/Bullet.h"
#include "BaseModel.h"


class BulletModel : public BaseModel {
public:
    void loadStatic() override;
    void draw(const Bullet &bullet, const GLuint &modelViewMatrixLocation);
};
