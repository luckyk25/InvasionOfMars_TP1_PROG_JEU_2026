#pragma once
#include "GameObject.h"

class Alien : public GameObject
{
public:
	Alien();
	~Alien();
	void init(const int alienTextureNumber);
	void update();
	void draw(sf::RenderWindow& window);
	static Vector2f destination;
	static void setDestination(const Vector2f& destination);

private:
	const int SPAWN_SPEED = 60;
	const Vector2i WORLD_SIZE;
	const float MIN_DISTANCE = 100.f;
	const float MOVE_SPEED = 4.0f;

	int spawnTimer = 0;
	float moveAngle = 0.0f;
	bool isMoving = false;
	Angle rotationAngle;

	void moveTowardDestination();
	void spawnAlien();
	void stop();
};

