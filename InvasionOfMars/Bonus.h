#pragma once
#include "GameObject.h"

class Bonus : public GameObject
{
	public:
		Bonus();
		void init(const int textureNumber);
	private:
		int durationTimer;
};