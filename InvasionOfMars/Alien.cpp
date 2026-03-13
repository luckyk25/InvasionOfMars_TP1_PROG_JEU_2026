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

void Alien::setDestination()
{
	
}