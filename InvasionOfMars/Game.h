#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Inputs.h"
#include "Player.h"
#include "Alien.h"
#include "Hud.h"
#include "Bullet.h"

using namespace sf;
using std::optional;

class Game
{
public:
	Game();
	int run();

private:
	const int WORLD_CENTER_X = WORLD_WIDTH / 2;
	const int WORLD_CENTER_Y = WORLD_HEIGHT / 2;

	//Puisque la utilise des positions centrales, les limites d'affichage
	//sont les positions centrales des cadres limites.
	const float WORLD_LIMIT_MIN_X = SCREEN_WIDTH / 2.0f;
	const float WORLD_LIMIT_MIN_Y = SCREEN_HEIGHT / 2.0f;
	const float WORLD_LIMIT_MAX_X = WORLD_WIDTH - WORLD_LIMIT_MIN_X;
	const float WORLD_LIMIT_MAX_Y = WORLD_HEIGHT - WORLD_LIMIT_MIN_Y;

	Bullet bullets[NBR_BULLETS];
	int recoil = 0;

	float playerRespawnTimer = 0.0f;
	float playerInvincibleTimer = 0.0f;
	int alienSpawnTimer = ALIEN_SPAWN_SPEED;
	
	bool playerInvincible = false;
	bool init();
	void getInputs();
	void update();
	void draw();
	void fire();
	bool unload();

	void calculateDeltaTime();

	void ajustCrossingWorldLimits();
	void managePlayerMovment();
	void managePlayerRespawn();
	void checkBulletAlienCollision();
	void checkPlayerAlienCollision();

	RenderWindow renderWindow;
	View mainView;
	View hudView;

    Clock clock;
	float deltaTime;

	Inputs inputs;

	Hud hud;
	Music music;

	Sprite* field = nullptr;
	Player player;

	Alien aliens[DEFAULT_ALIEN_COUNT];
};