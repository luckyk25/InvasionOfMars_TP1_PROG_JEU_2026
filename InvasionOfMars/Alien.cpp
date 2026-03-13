#include "Alien.h"
#include "ContentPipeline.h"

Alien::Alien() : WORLD_SIZE(WORLD_WIDTH, WORLD_HEIGHT)
{
}

Alien::~Alien()
{

}

void Alien::init(const int alienTextureNumber)
{
	setTexture(ContentPipeline::getInstance().getAlienTexture(alienTextureNumber));
}

void Alien::update(sf::Vector2f playerPosition)
{
	if (!isActive())
	{
		if (--spawnTimer <= 0) spawnAlien(playerPosition);
	}
	setDestination(playerPosition);
	if (isMoving)
	{
		if ((abs(destination.x - getPosition().x) <= (MOVE_SPEED / 2.0f)) && (abs(destination.y - getPosition().y) <= (MOVE_SPEED / 2.0f)))
		{
			setPosition(destination.x, destination.y);

			stop();
		}
		else
		{
			move(cos(moveAngle) * MOVE_SPEED, sin(moveAngle) * MOVE_SPEED);
		}
	}
}

void Alien::spawnAlien(sf::Vector2f playerPosition)
{
	spawnTimer = SPAWN_SPEED;

	int alienSizeX = getGlobalBounds().size.x;
	int alienSizeY = getGlobalBounds().size.y;

	float alienXPosition;
	float alienYPosition;

	do
	{
		alienXPosition = (rand() % (WORLD_SIZE.x - alienSizeX)) + alienSizeX / 2;
		alienYPosition = (rand() % (WORLD_SIZE.y - alienSizeY)) + alienSizeY / 2;
	} 
	while (sqrt((alienXPosition - playerPosition.x) *
				(alienXPosition - playerPosition.x) +
				(alienYPosition - playerPosition.y) *
				(alienYPosition - playerPosition.y)) <= MIN_DISTANCE);

	setPosition(alienXPosition, alienYPosition);
	activate();
}

void Alien::draw(sf::RenderWindow& window)
{
	window.draw(*this);
}

void Alien::setDestination(const Vector2f& destination)
{
	this->destination = destination;

	moveAngle = atan2f((destination.y - getPosition().y), (destination.x - getPosition().x));
	isMoving = true;
}

void Alien::stop()
{
	isMoving = false;
}