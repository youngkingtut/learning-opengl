#pragma once

#define GAME_TITLE "InsertGameTitle"
#define FPS_60 0.016F

// Window settings
#define WINDOW_SIZE_WIDTH 800.0F
#define WINDOW_SIZE_HEIGHT 600.0F
#define WINDOW_ASPECT_RATIO 1.33F
#define JOYSTICK_DEAD_ZONE_LOWER 0.2

// Game Dimensions
#define FOV 0.872665F // 50 degrees in radians
#define WORLD_SIZE_WIDTH 120.0F
#define WORLD_SIZE_HEIGHT 90.0F
#define WORLD_DEATH_COOL_DOWN 2.0F
#define PLAYER_RADIUS 2.0F
#define PLAYER_BOUNDARY 0.5F
#define BULLET_SPREAD 0.3F
#define BULLET_RADIUS 1.6F
#define CHASER_ENEMY_RADIUS 3.5F
#define SIMPLE_ENEMY_RADIUS 5.0F

// Game mechanics
#define DECELERATION 230.0F
#define ACCELERATION 250.0F
#define PLAYER_MAX_VELOCITY 80.0F
#define PLAYER_MAX_VELOCITY_THRESHOLD 0.8F
#define BULLET_MAX_VELOCITY 170.0F
#define ENEMY_MAX_VELOCITY 40.0F
#define PLAYER_BULLET_COOL_DOWN 0.1F

// Enemy Spawn Constants
#define SPAWN_ENEMIES true
#define WORLD_ENEMY_COOL_DOWN 0.5F
#define RANDOM_SPAWN_PLAYER_SAFE_ZONE_RADIUS 40.0F

// Shader UniForms
#define PROJECTION_MATRIX "projectionMatrix"
#define VIEW_MATRIX "viewMatrix"
#define MODEL_MATRIX "modelMatrix"
#define OBJECT_COLOR "objectColor"
