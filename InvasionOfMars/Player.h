#pragma once
#include "GameObject.h"
#include "Constants.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void init();
	void setPlayerDirection(const Vector2f& direction);
	void update();
	void keepPlayerInBound();
	Vector2f getVectorialPush();
	void switchTransparence(const bool isTransparent);
	void switchYellow(const bool isYellow);
	void playDeathSound();
private:
	Vector2f direction;
	float leftBound;
	float rightBound;
	float upBound;
	float downBound;
	Vector2f vectorialPush = Vector2f(0.0f, 0.0f);
	Sound* deathSound = nullptr;
};