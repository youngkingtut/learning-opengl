#include <math.h>
#include "Player.h"


void Player::initialize(float x, float y, float dir) {
    x_position = x;
    y_position = y;
    if(dir < 0 || dir > M_2_PI) {
        direction = 0;
    } else {
        direction = dir;
    }
}
