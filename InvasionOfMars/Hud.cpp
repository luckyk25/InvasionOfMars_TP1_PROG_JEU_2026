#include "Hud.h"
#include "ContentPipeline.h"

Hud::Hud()
{
}

Hud::~Hud()
{
	if (scoreText != nullptr) delete scoreText;
	if (nbLivesText != nullptr) delete nbLivesText;
	if (pauseText != nullptr) delete pauseText;
	if (gameOverText != nullptr) delete gameOverText;
}

void Hud::hudInit()
{
	score = 0;

	scoreText = new Text(ContentPipeline::getInstance().getFont(), "Score: " + std::to_string(score), 30U);
	scoreText->setFillColor(Color::White);
	scoreText->setPosition({ 10.0f, 20.0f });

	nbLivesText = new Text(ContentPipeline::getInstance().getFont(), "Vies: X" + std::to_string(nbLifes), 30u);
	nbLivesText->setFillColor(Color::White);
	nbLivesText->setPosition({ 10.0f, 60.0f });

	pauseText = new Text(ContentPipeline::getInstance().getFont(), PAUSE_TEXT, 100u);
	pauseText->setFillColor(Color::White);
	//https://www.sfml-dev.org/documentation/2.3/classsf_1_1Rect.php
	pauseText->setOrigin(pauseText->getLocalBounds().getCenter());
	pauseText->setPosition({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

	gameOverText = new Text(ContentPipeline::getInstance().getFont(), GAME_OVER_TEXT, 100u);
	gameOverText->setFillColor(Color::White);
	gameOverText->setOrigin(gameOverText->getLocalBounds().getCenter());
	gameOverText->setPosition({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });

}

bool Hud::isPlayerDead() 
{
	if (nbLifes <= 0) 
	{
		return true;
	}
	else
		return false;
}

void Hud::incrementScore() 
{
	int currentKillIncrement = DEFAULT_SCORE_INCREMENT;
	if(scoreBonusTimer > 0)
	{
		currentKillIncrement += BONUS_SCORE_INCREMENT;
		if (currentKillIncrement > BONUS_SCORE_INCREMENT_LIMIT)
			currentKillIncrement = BONUS_SCORE_INCREMENT_LIMIT;
	}
	score += currentKillIncrement;

	scoreBonusTimer = BONUS_SCORE_TIMER;


	scoreText->setString("Score" + std::to_string(score));
}

void Hud::update() 
{
	scoreBonusTimer--;
	nbLivesText->setString("Vies: X" + std::to_string(nbLifes));
}

void Hud::decreaseNumberOfLives() 
{
	nbLifes--;
}

void Hud::displayPause(const bool isPause)
{
	if (isPause)
		pauseState = true;
	else
		pauseState = false;
}

void Hud::draw(RenderWindow& renderWindow)
{
	renderWindow.draw(*scoreText);
	renderWindow.draw(*nbLivesText);
	if(pauseState)
		renderWindow.draw(*pauseText);
	if (isPlayerDead())
		renderWindow.draw(*gameOverText);
}