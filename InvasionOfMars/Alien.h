#pragma once
#include "GameObject.h"

class Alien : public GameObject
{
public:
	Alien();
	~Alien();
	void init(const int alienTextureNumber);
	void update(sf::Vector2f playerPosition);
	void draw(sf::RenderWindow& window);

private:
	const int SPAWN_SPEED = 60;
	const Vector2i WORLD_SIZE;
	const float MIN_DISTANCE = 100.f;

	void setDestination(const Vector2f& destination);
	void spawnAlien(sf::Vector2f playerPosition);
	int spawnTimer = 0;
};

