#pragma once


class ControlState {
public:
    void setUp(float up);
    void setDown(float down);
    void setRight(float right);
    void setLeft(float left);

    float getUp();
    float getDown();
    float getRight();
    float getLeft();

private:
    float up;
    float down;
    float left;
    float right;
};
