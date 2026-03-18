#include "Bonus.h"
#include "ContentPipeline.h"
#include <iostream>

Bonus::Bonus()
{

}

void Bonus::init(const int textureNumber)
{
	setTexture(ContentPipeline::getInstance().getLogoTexture(textureNumber));
	durationTimer = BONUS_SCORE_TIMER;
}