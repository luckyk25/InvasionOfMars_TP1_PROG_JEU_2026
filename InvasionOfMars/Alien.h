#pragma once
#include "GameObject.h"

class Alien : public GameObject
{
public:
	Alien(const int worldSizeX, const int worldSizeY);
	~Alien();
	void init(const int alienTextureNumber);
	void update(sf::Vector2f playerPosition);

private:
	const int SPAWN_SPEED = 60;
	const Vector2i WORLD_SIZE;
	const float MIN_DISTANCE = 300.f;

	void spawnAlien(sf::Vector2f playerPosition);
	int spawnTimer = 0;
};

