#include "Alien.h"
#include "ContentPipeline.h"

Vector2f Alien::destination;
bool Alien::toward;
Alien::Alien() : WORLD_SIZE(WORLD_WIDTH, WORLD_HEIGHT)
{
}

Alien::~Alien()
{

}

void Alien::init(const int alienTextureNumber)
{
	setTexture(ContentPipeline::getInstance().getAlienTexture(alienTextureNumber));
	toward = true;
	isMoving = true;
	spawnTimer = ALIEN_SPAWN_SPEED;
}

void Alien::update()
{
	if (!isActive() || !isMoving) return;
	moveTowardDestination();

}

void Alien::spawnAlien()
{
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

void Alien::changeDirection() 
{
	toward = !toward;
}

void Alien::setDestination(const Vector2f& _destination)
{
	destination = _destination;
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