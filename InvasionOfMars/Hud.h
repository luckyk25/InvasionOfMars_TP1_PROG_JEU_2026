#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

class Hud
{
public:
	Hud();
	~Hud();
	void hudInit();
	void pause();
	void draw(RenderWindow& renderWindow);
	void incrementScore();
	void update();
private:
	Text* bidon = nullptr;
	Text* scoreText = nullptr;
	float scoreBonusTimer = BONUS_SCORE_TIMER;

	int score;
};

