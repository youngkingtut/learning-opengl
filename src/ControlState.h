#pragma once


class ControlState {
public:
    void resetState();
    void setUp(float up);
    void setDown(float down);
    void setRight(float right);
    void setLeft(float left);

private:
    float up;
    float down;
    float left;
    float right;
};
