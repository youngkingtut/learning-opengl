#pragma once


class Player {
public:
    void initialize(float x, float y, float dir);

private:
    float x_position;
    float y_position;
    float direction;
};
