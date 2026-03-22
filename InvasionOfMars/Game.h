#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Inputs.h"
#include "Player.h"
#include "Alien.h"
#include "Hud.h"
#include "Bullet.h"
#include "Bonus.h"

using namespace sf;
using std::optional;

class Game
{
public:
	Game();
	int run();

private:
	const float WORLD_CENTER_X = WORLD_WIDTH / 2;
	const float WORLD_CENTER_Y = WORLD_HEIGHT / 2;

	//Puisque la utilise des positions centrales, les limites d'affichage
	//sont les positions centrales des cadres limites.
	const float WORLD_LIMIT_MIN_X = SCREEN_WIDTH / 2.0f;
	const float WORLD_LIMIT_MIN_Y = SCREEN_HEIGHT / 2.0f;
	const float WORLD_LIMIT_MAX_X = WORLD_WIDTH - WORLD_LIMIT_MIN_X;
	const float WORLD_LIMIT_MAX_Y = WORLD_HEIGHT - WORLD_LIMIT_MIN_Y;

	Bullet bullets[NBR_BULLETS];
	Bullet blasts[NBR_BLASTS];
	int recoil = 0;
	int blastRecoil = 0;

	float playerRespawnTimer = 0.0f;
	float playerInvincibleTimer = 0.0f;
	float playerSpeedBoost = 0.0f;
	int alienSpawnTimer = ALIEN_SPAWN_SPEED;
	
	bool boostOn = false;
	int boostTimer = 0;

	bool playerInvincible = false;
	bool gameOver = false;
	bool init();
	void getInputs();
	void update();
	void draw();

	void fire();
	void fireBlast();
	bool unload();

	void calculateDeltaTime();
	
	void managePlayerMovment();
	void managePlayerRespawn();
	void manageAlienSpawn();
	void manageGameConditions();
	void manageBonusSpawn(int j);

	void ajustCrossingWorldLimits();
	void checkBulletAlienCollision();
	void checkPlayerAlienCollision();
	void checkPlayerBonusCollision();

	void killAliensInRange();

	RenderWindow renderWindow;
	View mainView;
	View hudView;

    Clock clock;
	float deltaTime;

	Inputs inputs;

	Hud hud;
	Music music;

	Sprite* field = nullptr;
	bool isInPause = false;
	Player player;

	Bonus bonuses[NBR_BONUS_TYPE][NBR_OF_BONUS];
	Alien aliens[DEFAULT_ALIEN_COUNT];
};