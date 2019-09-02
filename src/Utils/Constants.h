#pragma once

#define GAME_TITLE "InsertGameTitle"
#define FPS_60 0.016f

// Window settings
#define WINDOW_SIZE_WIDTH 800.0f
#define WINDOW_SIZE_HEIGHT 600.0f
#define WINDOW_ASPECT_RATIO 1.33f
#define JOYSTICK_DEAD_ZONE 0.2

// Game Dimensions
#define FOV 0.872665f // 50 degrees in radians
#define WORLD_SIZE_WIDTH 54.0f
#define WORLD_SIZE_HEIGHT 40.0f
#define WORLD_ENEMY_COOL_DOWN 1.0f
#define WORLD_DEATH_COOL_DOWN 2.0f

#define PLAYER_RADIUS 1.2f
#define PLAYER_BOUNDARY 1.0f

#define BULLET_SIZE 0.5f
#define BULLET_RADIUS 0.5f

#define ENEMY_SIZE 6.0f
#define ENEMY_RADIUS 8.46f

// Game mechanics
#define DECELERATION 100.0f
#define ACCELERATION 250.0f
#define PLAYER_MAX_VELOCITY 60.0f
#define BULLET_MAX_VELOCITY 110.0f
#define ENEMY_MAX_VELOCITY 40.0f
#define PLAYER_BULLET_COOL_DOWN 0.1f
