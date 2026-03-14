#include "Bullet.h"

const float Bullet::BULLET_SPEED = 30.0f;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	if (bulletSound != nullptr) delete bulletSound;
}

void Bullet::setBulletSound(const SoundBuffer& soundBuffer)
{
	bulletSound = new Sound(soundBuffer);
}

void Bullet::fire(const GameObject& origin, const Vector2f& vectorialPush)
{
	setPosition(origin.getPosition());
	bulletMove.x = BULLET_SPEED * cos(origin.getRotation().asRadians());
	bulletMove.y = BULLET_SPEED * sin(origin.getRotation().asRadians());
	bulletMove += vectorialPush;

	lifeTime = MAX_LIFETIME;

	bulletSound->play();
	activate();
}

void Bullet::fly()
{
	if (!isActive()) return;

	move(bulletMove);
	setPosition(getPosition().x, getPosition().y);

	if (--lifeTime == 0) deactivate();
}
