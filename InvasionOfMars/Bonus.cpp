#include "Bonus.h"
#include "ContentPipeline.h"
#include <iostream>

Bonus::Bonus()
{
}

Bonus::~Bonus()
{
	if (toggleSound != nullptr) delete toggleSound;
	if (explosionSound != nullptr) delete explosionSound;
}

void Bonus::init(const int textureNumber)
{
	setTexture(ContentPipeline::getInstance().getLogoTexture(textureNumber));
	toggleSound = new Sound(ContentPipeline::getInstance().getTokenSoundBuffer());
	explosionSound = new Sound(ContentPipeline::getInstance().getExplosionSoundBuffer());
	durationTimer = EXTRA_SCORE_TIMER;
}

void Bonus::spawnBonus(Vector2f position) 
{
	this->setPosition(position);
	this->activate();
}

void Bonus::playExplosionSound() { explosionSound->play(); }
void Bonus::playToggleSound() { toggleSound->play(); }