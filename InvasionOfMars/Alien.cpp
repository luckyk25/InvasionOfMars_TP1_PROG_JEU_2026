#include "Alien.h"
#include "ContentPipeline.h"


Vector2f Alien::destination;
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

void Alien::update()
{
	if (!isActive())
	{
		if (--spawnTimer <= 0) spawnAlien();
		return;
	}

	moveTowardDestination();

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

void Alien::spawnAlien()
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
	while (sqrt((alienXPosition - destination.x) *
				(alienXPosition - destination.x) +
				(alienYPosition - destination.y) *
				(alienYPosition - destination.y)) <= MIN_DISTANCE);

	setPosition(alienXPosition, alienYPosition);
	activate();
}

void Alien::draw(sf::RenderWindow& window)
{
	window.draw(*this);
}

void Alien::setDestination(const Vector2f& _destination)
{
	destination = _destination;
}

void Alien::moveTowardDestination() 
{
	moveAngle = atan2f((destination.y - getPosition().y), (destination.x - getPosition().x));
	setRotation(sf::radians(moveAngle));
	isMoving = true;	
}

void Alien::stop()
{
	isMoving = false;
}