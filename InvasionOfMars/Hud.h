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
	void decreaseNumberOfLives();
	void displayPause(const bool isPause);
	bool isDead();
private:
	Text* scoreText = nullptr;
	Text* nbLivesText = nullptr;
	Text* pauseText = nullptr;
	Text* gameOverText = nullptr;
	bool pauseState = false;
	int nbLifes = DEFAULT_LIVES_NUMBER;
	float scoreBonusTimer = BONUS_SCORE_TIMER;

	int score;
};

