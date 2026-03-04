#pragma once
#include "GameObject.h"
#include "Constants.h"

class Player : public GameObject
{
public:
	Player();
	void init();
	void setPlayerDirection(const Vector2f& direction);
	void update();
	void keepPlayerInBound();

private:
	Vector2f direction;
	float leftBound;
	float rightBound;
	float upBound;
	float downBound;
};

