#include "Hud.h"
#include "ContentPipeline.h"

Hud::Hud()
{
}

Hud::~Hud()
{
	if (bidon != nullptr) delete bidon;
	if (scoreText != nullptr) delete scoreText;
}

void Hud::hudInit()
{
	score = 0;
	bidon = new Text(ContentPipeline::getInstance().getFont(), "Aliens are invading Mars!!!", 50U);
	bidon->setFillColor(Color::Red);
	bidon->setPosition({ 350.0f, 20.0f });

	scoreText = new Text(ContentPipeline::getInstance().getFont(), "Score: " + std::to_string(score), 50U);
	scoreText->setFillColor(Color::White);
	scoreText->setPosition({ 10.0f, 20.0f });
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
}

void Hud::pause() 
{

}


void Hud::draw(RenderWindow& renderWindow)
{
	renderWindow.draw(*bidon);
	renderWindow.draw(*scoreText);
}