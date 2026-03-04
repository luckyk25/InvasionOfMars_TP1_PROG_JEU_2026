#include "Player.h"
#include "ContentPipeline.h"
#include <cmath>
#include <iostream>
Player::Player()
{

}

void Player::init()
{
	setTexture(ContentPipeline::getInstance().getPlayerTexture());
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
}
