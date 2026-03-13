#include "Alien.h"
#include "ContentPipeline.h"

Alien::Alien(const int worldSizeX, const int worldSizeY) : WORLD_SIZE(worldSizeX, worldSizeY)
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
	if (--spawnTimer <= 0) spawnAlien(playerPosition);
}

void Alien::spawnAlien(sf::Vector2f playerPosition)
{
	spawnTimer = SPAWN_SPEED;

	int alienSizeX = getGlobalBounds().size.x;
	int alienSizeY = getGlobalBounds().size.y;


	//setPosition((rand() % (WORLD_SIZE.x - alienSizeX)) + alienSizeX / 2,
	//	(rand() % (WORLD_SIZE.y - alienSizeY)) + alienSizeY / 2);

}