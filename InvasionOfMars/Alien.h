#pragma once
#include "GameObject.h"

class Alien : public GameObject
{
public:
	Alien();
	~Alien();
	void init(const int alienTextureNumber, const SoundBuffer& soundBuffer);
	void update();
	static void setDestination(const Vector2f& destination);
	static void changeDirection();
	void spawnAlien();
	void stop();
	void run();
	void playDeathSound();


private:

	const Vector2i WORLD_SIZE;
	const float MIN_DISTANCE = 120.f;

	Sound* alienDeathSound = nullptr;

	static Vector2f destination;
	static bool toward;
	int spawnTimer = 0;
	float moveAngle = 0.0f;
	bool isMoving = false;
	Angle rotationAngle;

	void moveTowardDestination();
};

