#pragma once

#include "BaseModel.h"
#include "../../Game/Objects/Player.h"


class PlayerModel : public BaseModel {
public:
    void loadStatic() override;
    void draw(const Player &player, const GLuint& modelViewMatrixLocation, const GLuint& colorLocation);
private:
    glm::vec4 color = glm::vec4(1.0F, 0.0F, 1.0F, 1.0F);
};


