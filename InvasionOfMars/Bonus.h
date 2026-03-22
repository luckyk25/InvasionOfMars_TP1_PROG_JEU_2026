#pragma once
#include "GameObject.h"
#include "Alien.h"

class Bonus : public GameObject
{
	public:
		Bonus();
		void init(const int textureNumber);
		void spawnBonus(Vector2f position);
	private:
		int durationTimer;
		bool isRunning;
};