#pragma once
#include "GameObject.h"
#include "Alien.h"

class Bonus : public GameObject
{
	public:
		Bonus();
		~Bonus();
		void init(const int textureNumber);
		void spawnBonus(Vector2f position);
		void playExplosionSound();
		void playToggleSound();
	private:
		int durationTimer;
		bool isRunning;
		
		Sound* toggleSound = nullptr;
		Sound* explosionSound = nullptr;
};