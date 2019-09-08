#pragma once

#define GAME_TITLE "InsertGameTitle"
#define FPS_60 0.016f

// Window settings
#define WINDOW_SIZE_WIDTH 800.0f
#define WINDOW_SIZE_HEIGHT 600.0f
#define WINDOW_ASPECT_RATIO 1.33f
#define JOYSTICK_DEAD_ZONE_LOWER 0.15
#define JOYSTICK_DEAD_ZONE_UPPER 0.85

// Game Dimensions
#define SPAWN_ENEMIES false
#define FOV 0.872665f // 50 degrees in radians
#define WORLD_SIZE_WIDTH 120.0f
#define WORLD_SIZE_HEIGHT 90.0f
#define WORLD_ENEMY_COOL_DOWN 1.0f
#define WORLD_DEATH_COOL_DOWN 2.0f

#define PLAYER_RADIUS 2.0f
#define PLAYER_BOUNDARY 0.5f

#define BULLET_SPREAD 0.3f
#define BULLET_RADIUS 1.6f

#define ENEMY_RADIUS 3.5f

// Game mechanics
#define DECELERATION 230.0f
#define ACCELERATION 250.0f
#define PLAYER_MAX_VELOCITY 80.0f
#define BULLET_MAX_VELOCITY 140.0f
#define ENEMY_MAX_VELOCITY 40.0f
#define PLAYER_BULLET_COOL_DOWN 0.1f


// Shader Uniforms
#define PROJECTION_MATRIX "projectionMatrix"
#define VIEW_MATRIX "viewMatrix"
#define MODEL_MATRIX "modelMatrix"