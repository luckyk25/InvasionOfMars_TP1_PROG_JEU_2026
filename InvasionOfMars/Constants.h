#pragma once

//World
static const unsigned int SCREEN_WIDTH = 1280;
static const unsigned int SCREEN_HEIGHT = 720;

static const unsigned int WORLD_WIDTH = 3840;
static const unsigned int WORLD_HEIGHT = 2160;

const float PLAYER_LIMIT_MIN_X = 0.0f;
const float PLAYER_LIMIT_MIN_Y = 0.0f;
const float PLAYER_LIMIT_MAX_X = WORLD_WIDTH;
const float PLAYER_LIMIT_MAX_Y = WORLD_HEIGHT;

//Player
static const float PLAYER_SPEED = 5.0f;
static const float CAMERA_SPEED = PLAYER_SPEED;
static const float ROTATION_SPEED = 50.0f;

//Shooting
const int MAX_RECOIL = 10;
static const int NBR_BULLETS = 20;

//Game
const int PLAYER_RESPAWN_TIME = 180;

//Alien
const int DEFAULT_ALIEN_COUNT = 30;
const int ALIEN_SPAWN_SPEED = 60;
const float ALIEN_MOVE_SPEED = 4.0f;


//Math Helpers
const float DIAGONAL_RATIO = 0.70710678f;
const float PI = 3.14159265f;