#pragma once
#include "GameObject.h"

class Bonus : public GameObject
{
	public:
		Bonus();
		void init(const int textureNumber);
		void update();
		void spawnBonus(Vector2f position);
	private:
		int durationTimer;
		bool isRunning;
};