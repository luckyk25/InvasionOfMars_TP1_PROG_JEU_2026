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
	nbLifes = DEFAULT_LIVES_NUMBER;
	scoreText = new Text(ContentPipeline::getInstance().getFont(), "Score: " + std::to_string(score), 30U);
	scoreText->setFillColor(Color::White);
	scoreText->setPosition({ 10.0f, 20.0f });

	nbLivesText = new Text(ContentPipeline::getInstance().getFont(), "Vies: X" + std::to_string(nbLifes), 30u);
	nbLivesText->setFillColor(Color::White);
	nbLivesText->setPosition({ 10.0f, 60.0f });

	pauseText = new Text(ContentPipeline::getInstance().getFont(), PAUSE_TEXT, 100u);
	pauseText->setFillColor(Color::White);
	//https://www.sfml-dev.org/documentation/2.3/classsf_1_1Rect.php
	// cette manière permet de mettre l'origine sur le vrai centre du texte.
	pauseText->setOrigin(pauseText->getLocalBounds().getCenter());
	pauseText->setPosition({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

	gameOverText = new Text(ContentPipeline::getInstance().getFont(), GAME_OVER_TEXT, 100u);
	gameOverText->setFillColor(Color::White);
	gameOverText->setOrigin(gameOverText->getLocalBounds().getCenter());
	gameOverText->setPosition({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });

}

bool Hud::isPlayerDead() 
{
	//confirme si le joueur est mort.
	if (nbLifes <= 0) 
		return true;
	else
		return false;
}

void Hud::setCurrentKillScore(int currentScore)
{
	this->currentKillScore = currentScore;
}

void Hud::incrementScore() 
{
	int currentKillIncrement = DEFAULT_SCORE_INCREMENT;
	//Le temps n'est pas encore écoulé.
	if(scoreBonusTimer > 0)
	{
		//Incrementation avec bonus de 10.
		currentKillIncrement = currentKillScore + EXTRA_SCORE_INCREMENT;
		//Validation si la suite d'incrementation ne depasse pas la limite.
		if (currentKillIncrement > EXTRA_SCORE_INCREMENT_LIMIT)
			currentKillIncrement = EXTRA_SCORE_INCREMENT_LIMIT;
	}
	//permet de garder la valeur du kill actuel.
	//Je suspecte qu'il y avait une manière plus optimale de le fair, mais cette façon semble marcher.
	setCurrentKillScore(currentKillIncrement);

	score += currentKillIncrement;
	
	//Le compteur de score pour obtenir le nombre de vies pour savoir si on peut rajouter une vie.
	scoreToGetLife += currentKillIncrement;

	if (scoreToGetLife >= SCORE_TO_GET_EXTRA_LIFE)
	{
		nbLifes++;
		scoreToGetLife -= SCORE_TO_GET_EXTRA_LIFE;
	}
	scoreBonusTimer = EXTRA_SCORE_TIMER;
	scoreText->setString("Score" + std::to_string(score));
}

void Hud::update() 
{
	if(scoreBonusTimer > 0)
		scoreBonusTimer--;
	nbLivesText->setString("Vies: X" + std::to_string(nbLifes));
}

void Hud::decreaseNumberOfLives() 
{
	nbLifes--;
}

void Hud::displayPause(const bool isPause)
{
	//gestion de la pause.
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
		//affiche la mort du joueur.
		renderWindow.draw(*gameOverText);
}

int Hud::getCurrentKillScore()
{
	return currentKillScore;
}