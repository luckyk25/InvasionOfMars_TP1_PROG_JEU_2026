#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

struct Inputs
{
	const float DEAD_ZONE = 20.0f;
	const float ROTATION_SPEED = 5.0f;

	Inputs()
	{
		reset();
	}

	void reset()
	{
		moveVertical = 0.0f;
		moveHorizontal = 0.0f;
		rotation = 0.0f;
		mousePosition = sf::Vector2f(0.0f, 0.0f);
		//Peut-être pratique de sauvegarder le fait
		//que le gamepad soit actif ou non (voir game.getInputs)
		fire = false;
		bool isGamepadActive = false;
		pause = false;
	}	

	//Portée analogue -100 à 100
	float manageGamepadAxis(const float axisValue)
	{
		if (abs(axisValue) < DEAD_ZONE) return 0.0f;
		return axisValue / 100.0f;
	}

	void adjustInputs()
	{
		if(this->moveHorizontal != 0 && this->moveVertical != 0) 
		{
			moveVertical *= DIAGONAL_RATIO;
			moveHorizontal *= DIAGONAL_RATIO;
		}
	}

	float convertJoystickAxis(float axisValue)
	{
		if (abs(axisValue) <= DEAD_ZONE) { return 0.0f; }
		return axisValue / 100.0f;
	}

	float moveVertical;
	float moveHorizontal;
	float rotation;
	bool fire;
	bool pause;
	bool isGamepadActive;
	sf::Vector2f mousePosition;
};

