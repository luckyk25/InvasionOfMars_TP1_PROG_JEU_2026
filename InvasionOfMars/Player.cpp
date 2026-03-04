#include "Player.h"
#include "ContentPipeline.h"
#include <iostream>
Player::Player()
{

}

void Player::init()
{
	setTexture(ContentPipeline::getInstance().getPlayerTexture());
	leftBound = getTexture().getSize().x / 2.f;
	rightBound = WORLD_WIDTH - getTexture().getSize().x / 2.f;
	upBound = getTexture().getSize().y / 2.f;
	downBound = WORLD_HEIGHT - getTexture().getSize().y / 2.f;
	activate();
}

void Player::setPlayerDirection(const Vector2f& direction)
{
	this->direction = direction;
	float moveAngle = atan2f((direction.y - getPosition().y), (direction.x - getPosition().x));
	this->setRotation(radians(moveAngle));
}

void Player::update() 
{
	std::cout << "x = " << this->getPosition().x << " y = " << this->getPosition().y;
}

void Player::keepPlayerInBound()
{
	if (getPosition().x < leftBound)
		setPosition(leftBound, getPosition().y);
	else if (getPosition().x > rightBound)
			setPosition(rightBound, getPosition().y);

	if (getPosition().y < upBound) 
			setPosition(getPosition().y, upBound);
	else if (getPosition().y > downBound)
			setPosition(getPosition().y, downBound);
}
