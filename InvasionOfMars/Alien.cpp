#include "Alien.h"
#include "ContentPipeline.h"

Vector2f Alien::destination;
bool Alien::toward;
Alien::Alien() : WORLD_SIZE(WORLD_WIDTH, WORLD_HEIGHT)
{
}

Alien::~Alien()
{
	if (alienDeathSound != nullptr) delete alienDeathSound;
	if (scoreText != nullptr) delete scoreText;
}

void Alien::init(const int alienTextureNumber, const SoundBuffer& soundBuffer)
{
	this->setTexture(ContentPipeline::getInstance().getAlienTexture(alienTextureNumber));
	scoreText = new Text(ContentPipeline::getInstance().getFont(), "", 20u);
	scoreText->setFillColor(Color::White);
	alienDeathSound = new Sound(soundBuffer);
	toward = true;
	isMoving = true;
	spawnTimer = ALIEN_SPAWN_SPEED;
}

void Alien::update()
{
	if (!isActive() || !isMoving) return;
	moveTowardDestination();
	if (scoreText > 0)
		scoreTextTimer--;
}

void Alien::spawnAlien()
{
	float alienSizeX = getGlobalBounds().size.x;
	float alienSizeY = getGlobalBounds().size.y;
	float alienXPosition;
	float alienYPosition;

	do
	{
		//https://www.geeksforgeeks.org/cpp/static_cast-in-cpp/
		alienXPosition = (rand() % static_cast<int>(WORLD_SIZE.x - alienSizeX)) + alienSizeX / 2.f;
		alienYPosition = (rand() % static_cast<int>(WORLD_SIZE.y - alienSizeY)) + alienSizeY / 2.f;
	} 
	while (sqrt((alienXPosition - destination.x) *
				(alienXPosition - destination.x) +
				(alienYPosition - destination.y) *
				(alienYPosition - destination.y)) <= MIN_DISTANCE);

	setPosition(alienXPosition, alienYPosition);
	activate();
}

void Alien::changeDirection() 
{
	toward = !toward;
}

void Alien::setDestination(const Vector2f& _destination)
{
	destination = _destination;
}

void Alien::draw(RenderWindow& renderWindow)
{
	if (isActive())
		renderWindow.draw(*this);

	if (scoreTextTimer > 0)
		renderWindow.draw(*scoreText);
}

void Alien::moveTowardDestination() 
{
	float dx = destination.x - getPosition().x;
	float dy = destination.y - getPosition().y;
	float dist = sqrt(dx * dx + dy * dy);

	if (toward)
	{
		if (dist < DISTANCE_TOLERANCE)
		{
			return;
		}
	}
	moveAngle = atan2f(dy, dx);
	if (!toward) moveAngle += PI;
	setRotation(sf::radians(moveAngle));
	move(cos(moveAngle) * ALIEN_MOVE_SPEED, sin(moveAngle) * ALIEN_MOVE_SPEED);
}

void Alien::run() 
{
	isMoving = true;
}

void Alien::stop()
{
	isMoving = false;
}

void Alien::playDeathSound()
{
	alienDeathSound->play();
}

void Alien::displayAlienDeathScore(const int score) 
{
	scoreTextTimer = DEFAULT_SCORE_DISPLAY_TIMER;
	scoreText->setString(std::to_string(score));
	scoreText->setOrigin(scoreText->getLocalBounds().getCenter());
	scoreText->setPosition(getPosition());
}

void Alien::alienDead(const int deathScore) 
{
	this->deactivate();
	playDeathSound();
	displayAlienDeathScore(deathScore);
}