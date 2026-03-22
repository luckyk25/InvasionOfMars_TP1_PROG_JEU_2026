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
	void draw(RenderWindow& renderWindow);
	void incrementScore();
	void update();
	void decreaseNumberOfLives();
	void displayPause(const bool isPause);
	bool isPlayerDead();
	int getCurrentKillScore();
private:
	Text* scoreText = nullptr;
	Text* nbLivesText = nullptr;
	Text* pauseText = nullptr;
	Text* gameOverText = nullptr;
	
	bool pauseState = false;
	int nbLifes = DEFAULT_LIVES_NUMBER;
	int currentKillScore = 0;
	float scoreBonusTimer = EXTRA_SCORE_TIMER;

	void setCurrentKillScore(int currentKillScore);

	int score;
};

