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
private:
	Vector2f direction;
};

