#include "Bonus.h"
#include "ContentPipeline.h"
#include <iostream>

Bonus::Bonus()
{

}

void Bonus::init(const int textureNumber)
{
	setTexture(ContentPipeline::getInstance().getLogoTexture(textureNumber));
	durationTimer = EXTRA_SCORE_TIMER;
}


void Bonus::spawnBonus(Vector2f position) 
{
	this->setPosition(position);
	this->activate();
}