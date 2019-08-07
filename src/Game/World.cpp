#include "World.h"

#include <iostream>
#include "../Utils/Constants.h"


World::World() :
bullets(),
cooldown(0.0f),
player(vmath::vec2(20, 20), vmath::vec2(0, 0), vmath::vec2(0, 0), 0),
size(vmath::vec2(400, 300))
{
    lower_x = -size[0];
    lower_y = -size[1];
    upper_x = size[0];
    upper_y = size[1];
}

vmath::vec2 World::getSize() const {
    return size;
}

Player World::getPlayer() const {
    return player;
}

std::vector<Bullet> World::getBullets() const {
    return bullets;
}

void World::update(const ControlState& controlState, double deltaTime) {
    // Update player position
    vmath::vec2 playerPosition = player.setNextPosition(controlState, deltaTime);
    playerPosition = BoundaryCheck(playerPosition, player.getSize() / 2);
    player.setPosition(playerPosition);

    // Generate Bullets
    cooldown += deltaTime;
    if(cooldown > 0.01f && controlState.getBulletMagnitude() > 0) {
        cooldown = 0.0f;
        vmath::vec2 bulletDirection = controlState.getBulletDirection();
        Bullet bullet = Bullet(vmath::vec2(5, 5), playerPosition, BULLET_VELOCITY * vmath::normalize(bulletDirection), 0);
        this->bullets.push_back(bullet);
    }

    // Get next bullet position and remove out of bounds bullets
    for(auto & bullet : bullets) {
        vmath::vec2 bulletPosition = bullet.setNextPosition(controlState, deltaTime);
        bullet.setRemove(outOfBounds(bullet.getPosition(), bullet.getSize() / 2));
    }
    auto new_end = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){return b.shouldRemove();});
    bullets.erase(new_end, bullets.end());
}

vmath::vec2 World::BoundaryCheck(vmath::vec2 position, vmath::vec2 s) {
    if(position[0] + s[0] > upper_x) {
        position[0] = upper_x - s[0];
    } else if (position[0] - s[0] < lower_x) {
        position[0] = lower_x + s[0];
    }

    if(position[1] + s[1] > upper_y) {
        position[1] = upper_y - s[1];
    } else if (position[1] - s[1] < lower_y) {
        position[1] = lower_y + s[1];
    }

    return position;
}

bool World::outOfBounds(vmath::vec2 position, vmath::vec2 s) {
    if(position[0] + s[0] > upper_x || position[0] - s[0] < lower_x) {
        return true;
    }

    return position[1] + s[1] > upper_y || position[1] - s[1] < lower_y;
}
