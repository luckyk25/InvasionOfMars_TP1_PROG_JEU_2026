#pragma once
static const unsigned int SCREEN_WIDTH = 1280;
static const unsigned int SCREEN_HEIGHT = 720;

static const unsigned int WORLD_WIDTH = 3840;
static const unsigned int WORLD_HEIGHT = 2160;

const float PLAYER_LIMIT_MIN_X = 0.0f;
const float PLAYER_LIMIT_MIN_Y = 0.0f;
const float PLAYER_LIMIT_MAX_X = WORLD_WIDTH;
const float PLAYER_LIMIT_MAX_Y = WORLD_HEIGHT;
static const float PLAYER_SPEED = 5.0f;
static const float CAMERA_SPEED = PLAYER_SPEED;
static const float ROTATION_SPEED = 50.0f;

const float DIAGONAL_RATIO = 0.70710678f;

const int DEFAULT_ALIEN_COUNT = 4;