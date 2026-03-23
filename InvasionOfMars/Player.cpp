#include "Player.h"
#include "ContentPipeline.h"
#include <iostream>
Player::Player()
{
}

Player::~Player() 
{
	if(deathSound != nullptr) delete deathSound;
}

void Player::init()
{
	setTexture(ContentPipeline::getInstance().getPlayerTexture());
	deathSound = new Sound(ContentPipeline::getInstance().getPlayerDeathBuffer());
	leftBound = getTexture().getSize().x / 2.f;
	rightBound = WORLD_WIDTH - getTexture().getSize().x / 2.f;
	upBound = getTexture().getSize().y / 2.f;
	downBound = WORLD_HEIGHT - getTexture().getSize().y / 2.f;
	activate();
}

void Player::setPlayerDirection(const Vector2f& direction)
{
	//Obtient la direction finale, trouve l'angle requis, tourne le joueur sélon l'angle par rapport à la direction.
	this->direction = direction;
	float moveAngle = atan2f((direction.y - getPosition().y), (direction.x - getPosition().x));
	this->setRotation(radians(moveAngle));
}

void Player::update() 
{
}

void Player::keepPlayerInBound()
{
	//Empeche le jouer de quitter les limites du monde.
	//les bounds sont predefinis en avance. Limite +/- la moitié de la taille de la texture.
	if (getPosition().x < leftBound)
		setPosition(leftBound, getPosition().y);
	else if (getPosition().x > rightBound)
			setPosition(rightBound, getPosition().y);

	if (getPosition().y < upBound)
		setPosition(getPosition().x, upBound);
	else if (getPosition().y > downBound)
		setPosition(getPosition().x, downBound);
}

Vector2f Player::getVectorialPush()
{
	return vectorialPush;
}

void Player::switchTransparence(const bool isTransparent)
{
	/*
	fait à partir de l'exemple donné par Gemini AI
		sf::Texture texture;
		texture.loadFromFile("image.png");
		sf::Sprite sprite(texture);
		sprite.setColor(sf::Color(255, 255, 255, 128));

	j'ai utilisé l'IA pour le trouver plus rapidement.
	J'ai compris par essaye erruer que la couleur a(Alpha) definit la transparence. avec une valeur entre 0 et 255.
	*/
	Color color = this->getColor();
	if (isTransparent) 
	{
		color.a = 80;
		this->activate();
	}
	else
		color.a = 255;

	this->setColor(color);
}

void Player::switchYellow(const bool isYellow) 
{
	//Change la couleur du joueur. Rend jaune si besoin.
	// Si j'avais le temps j'aurais du utiliser un switch case avec 3 cas. Transparent, Doré, Normal.
	if (isYellow)
		// TODO si le temps mettre en const
		this->setColor(sf::Color(255, 255, 0));
	else
		this->setColor(sf::Color::White);
}

void Player::playDeathSound()
{
	deathSound->play();
}