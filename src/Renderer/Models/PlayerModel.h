#pragma once

#include "BaseModel.h"
#include "../../Game/Objects/Player.h"


class PlayerModel : public BaseModel {
public:
    void loadStatic() override;
    void draw(const Player &player, const GLuint &modelViewMatrixLocation);
};


