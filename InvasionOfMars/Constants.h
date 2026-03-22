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
static const float DEFAULT_SPEED_BOOST = 2.5f;
static const float CAMERA_SPEED = PLAYER_SPEED;
static const float ROTATION_SPEED = 50.0f;

//Shooting
const int MAX_RECOIL = 10;
static const int MAX_BLAST_RECOIL = MAX_RECOIL * 2;
static const int NBR_BULLETS = 20;
static const int NBR_BLASTS = 18;

//Game
const int PLAYER_RESPAWN_TIME = 120;
const int INVINCIBLE_TIMER = 180;
const int BONUS_SPAWN_RATE = 25;
const int NBR_OF_BONUS = 6;
const int NBR_BONUS_TYPE = 2;
const int MUSIC_COUNT = 3;
const int BULLET = 1;
const int BLAST = 0;

//Boosters
const int NUKE_NUMBER = 1;
const int BOOSTER = 0;
const int BONUS_DURATION = 300;// 60 * 5 sec

//Alien
const int ALIEN_SPAWN_SPEED = 60;
const int DEFAULT_ALIEN_COUNT = 160;
const float ALIEN_MOVE_SPEED = 4.0f;
const float DISTANCE_TOLERANCE = 15.0f;

//Math Helpers
const float DIAGONAL_RATIO = 0.70710678f;
const float PI = 3.14159265f;

//Hud
const std::string PAUSE_TEXT = "Pause";
const std::string GAME_OVER_TEXT = "Game Over";
const int DEFAULT_SCORE_INCREMENT = 100;
const int DEFAULT_LIVES_NUMBER = 5;
const int DEFAULT_SCORE_DISPLAY_TIMER = 25;
const int EXTRA_SCORE_INCREMENT_LIMIT = 500;
const int EXTRA_SCORE_INCREMENT = 10;
const int EXTRA_SCORE_TIMER = 60;