#include "Alien.h"
#include "ContentPipeline.h"

Vector2f Alien::destination;
bool Alien::toward;
Alien::Alien() : WORLD_SIZE(WORLD_WIDTH, WORLD_HEIGHT)
{
}

Alien::~Alien()
{
	if (alienDeathSound != nullptr) delete alienDeathSound;
	if (scoreText != nullptr) delete scoreText;
}

void Alien::init(const int alienTextureNumber, const SoundBuffer& soundBuffer)
{
	this->setTexture(ContentPipeline::getInstance().getAlienTexture(alienTextureNumber));
	scoreText = new Text(ContentPipeline::getInstance().getFont(), "", 20u);
	scoreText->setFillColor(Color::White);
	alienDeathSound = new Sound(soundBuffer);
	toward = true;
	isMoving = true;
	spawnTimer = ALIEN_SPAWN_SPEED;
}

void Alien::calculateMoveAngle() 
{
	float dx = destination.x - getPosition().x;
	float dy = destination.y - getPosition().y;
	moveAngle = atan2f(dy, dx);
	if (!toward) moveAngle += PI;
}

void Alien::update()
{
	if (scoreText > 0)
		scoreTextTimer--;

	if(isSpawning) 
	{
		spawnTimer --;
		//Quand le timer est à 0. Le progress est a 100% (à 1). donc l'alein se rend à son scale de 1.
		float progress = 1.f - (spawnTimer / ALIEN_SPAWN_SPEED);
		setScale({ progress, progress });
		calculateMoveAngle();
		// J'ai utilisé gemini ai pour mieux comprendre le principe. 
		// le offset rend l'alien en petit peu tourné par rapport au "vrai" angle
		// pour se rendre vers le joueur.
		// quand le progress est a 0% il rajoute 360 degress.
		float rotationOffsetDegrees = (1.f - progress) * 360.f;
		setRotation(sf::degrees(sf::radians(moveAngle).asDegrees() + rotationOffsetDegrees));
		//Après 1 seconde. Le scale est normal. l'alien n'est plus invincible.
		if (spawnTimer <= 0)
		{
			isSpawning = false;
			setScale({ 1.f, 1.f });
		}
		return;
	}
	if (!isMoving) return;
	moveTowardDestination();
}

void Alien::spawnAlien()
{
	float alienSizeX = getGlobalBounds().size.x;
	float alienSizeY = getGlobalBounds().size.y;
	float alienXPosition;
	float alienYPosition;

	do
	{
		//https://www.geeksforgeeks.org/cpp/static_cast-in-cpp/
		alienXPosition = (rand() % static_cast<int>(WORLD_SIZE.x - alienSizeX)) + alienSizeX / 2.f;
		alienYPosition = (rand() % static_cast<int>(WORLD_SIZE.y - alienSizeY)) + alienSizeY / 2.f;
	} 
	while (sqrt((alienXPosition - destination.x) *
				(alienXPosition - destination.x) +
				(alienYPosition - destination.y) *
				(alienYPosition - destination.y)) <= MIN_DISTANCE);

	setPosition(alienXPosition, alienYPosition);
	//Scale initiale. L<alien est super petit.
	setScale({ 0.f, 0.f });
	isSpawning = true;
	spawnTimer = ALIEN_SPAWN_SPEED;
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

void Alien::draw(RenderWindow& renderWindow)
{
	if (isActive())
		renderWindow.draw(*this);

	if (scoreTextTimer > 0)
		renderWindow.draw(*scoreText);
}

void Alien::moveTowardDestination() 
{
	float dx = destination.x - getPosition().x;
	float dy = destination.y - getPosition().y;
	float dist = sqrt(dx * dx + dy * dy);

	if (toward && dist < DISTANCE_TOLERANCE)
			return;

	calculateMoveAngle();
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

void Alien::playDeathSound()
{
	alienDeathSound->play();
}

void Alien::displayAlienDeathScore(const int score) 
{
	scoreTextTimer = DEFAULT_SCORE_DISPLAY_TIMER;
	scoreText->setString(std::to_string(score));
	scoreText->setOrigin(scoreText->getLocalBounds().getCenter());
	scoreText->setPosition(getPosition());
}

void Alien::alienDead(const int deathScore) 
{
	this->deactivate();
	playDeathSound();
	displayAlienDeathScore(deathScore);
}

bool Alien::getIsSpawning() { return isSpawning; }