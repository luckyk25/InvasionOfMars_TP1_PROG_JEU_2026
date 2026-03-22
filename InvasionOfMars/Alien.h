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
	void alienDead(const int deathScore);
	void draw(RenderWindow& renderWindow);
	bool getIsSpawning();
	void calculateMoveAngle();
private:

	const Vector2i WORLD_SIZE;
	const float MIN_DISTANCE = 120.0f;

	Sound* alienDeathSound = nullptr;
	Text* scoreText = nullptr;
	float scoreTextTimer = 0.0f;

	static Vector2f destination;
	static bool toward;
	float moveAngle = 0.0f;

	float spawnTimer = 0.0f;
	bool isSpawning = false;

	bool isMoving = false;
	Angle rotationAngle;

	void playDeathSound();
	void displayAlienDeathScore(const int deathScore);
	void moveTowardDestination();
};

