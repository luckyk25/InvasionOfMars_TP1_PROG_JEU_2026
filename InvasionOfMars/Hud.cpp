#include "Hud.h"
#include "ContentPipeline.h"

Hud::Hud()
{
}

Hud::~Hud()
{
	if (bidon != nullptr) delete bidon;
	if (scoreText != nullptr) delete scoreText;
	if (nbLivesText != nullptr) delete nbLivesText;
	if (pauseText != nullptr) delete pauseText;
}

void Hud::hudInit()
{
	score = 0;
	bidon = new Text(ContentPipeline::getInstance().getFont(), "Aliens are invading Mars!!!", 50U);
	bidon->setFillColor(Color::Red);
	bidon->setPosition({ 350.0f, 20.0f });

	scoreText = new Text(ContentPipeline::getInstance().getFont(), "Score: " + std::to_string(score), 30U);
	scoreText->setFillColor(Color::White);
	scoreText->setPosition({ 10.0f, 20.0f });

	nbLivesText = new Text(ContentPipeline::getInstance().getFont(), "Vies: X" + std::to_string(nbLifes), 30u);
	nbLivesText->setFillColor(Color::White);
	nbLivesText->setPosition({ 10.0f, 60.0f });

	pauseText = new Text(ContentPipeline::getInstance().getFont(), PAUSE_TEXTE, 100u);
	pauseText->setFillColor(Color::White);
	FloatRect textBounds = pauseText->getLocalBounds();
		pauseText->setOrigin(textBounds.getCenter());
	pauseText->setPosition({ SCREEN_WIDTH/2, SCREEN_HEIGHT / 2});
}

bool Hud::isDead() 
{
	if (nbLifes <= 0)
		return 1;
	else
		return 0;
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
}