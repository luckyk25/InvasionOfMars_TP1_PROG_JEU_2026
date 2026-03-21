#pragma once
#include "GameObject.h"
#include <SFML/Audio.hpp>

class Bullet : public GameObject 
{
	public:
		Bullet();
		~Bullet();
		void setBulletSound(const SoundBuffer& soundBuffer);
		void fire(const GameObject& origin, const Vector2f& vectorialPush);
		void fly();
		void setIsBlast(bool blast);
		bool getIsBlast();
	private: 
		static const int MAX_LIFETIME = 180;
		static const float BULLET_SPEED;
		
		bool isBlast = false;
		Vector2f bulletMove = Vector2f(0.0f, 0.0f);
		Sound* bulletSound = nullptr;
		int lifeTime = 0;
};