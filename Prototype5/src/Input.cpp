//==========================//
// Input.cpp                //
// Author: Matthew Stephens //
//==========================//
#include "Input.h"

//=============================
// Constructor()
//=============================
Input::Input()
{
	for (int i = 0; i < InputNS::NUM_BUTTONS; i++)
	{
		current[i] = false;
		pressed[i] = false;
		released[i] = false;
	}
}

//=========//
// Methods //
//=========//

void Input::getInput()
{
	int button;

	// Handle LEFT key
	button = (int)InputNS::LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		pressed[button] = !current[button];
		current[button] = true;
		released[button] = false;
	}
	else
	{
		released[button] = current[button];
		current[button] = false;
		pressed[button] = false;
	}

	// Handle RIGHT key
	button = (int)InputNS::RIGHT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		pressed[button] = !current[button];
		current[button] = true;
		released[button] = false;
	}
	else
	{
		released[button] = current[button];
		current[button] = false;
		pressed[button] = false;
	}

	// Handle UP key
	button = (int)InputNS::UP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		pressed[button] = !current[button];
		current[button] = true;
		released[button] = false;
	}
	else
	{
		released[button] = current[button];
		current[button] = false;
		pressed[button] = false;
	}

	// Handle DOWN key
	button = (int)InputNS::DOWN;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		pressed[button] = !current[button];
		current[button] = true;
		released[button] = false;
	}
	else
	{
		released[button] = current[button];
		current[button] = false;
		pressed[button] = false;
	}

	// Handle JUMP key
	button = (int)InputNS::JUMP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		pressed[button] = !current[button];
		current[button] = true;
		released[button] = false;
	}
	else
	{
		released[button] = current[button];
		current[button] = false;
		pressed[button] = false;
	}

	// Handle SHOOT key
	button = (int)InputNS::SHOOT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		pressed[button] = !current[button];
		current[button] = true;
		released[button] = false;
	}
	else
	{
		released[button] = current[button];
		current[button] = false;
		pressed[button] = false;
	}

	// Handle SEL_LASER key
	button = (int)InputNS::SEL_LASER;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		pressed[button] = !current[button];
		current[button] = true;
		released[button] = false;
	}
	else
	{
		released[button] = current[button];
		current[button] = false;
		pressed[button] = false;
	}

	// Handle SEL_FREEZE key
	button = (int)InputNS::SEL_FREEZE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		pressed[button] = !current[button];
		current[button] = true;
		released[button] = false;
	}
	else
	{
		released[button] = current[button];
		current[button] = false;
		pressed[button] = false;
	}
}

bool Input::isPressed(InputNS::button b)
{
	int button = (int)b;
	return current[b];
}

bool Input::wasPressed(InputNS::button b)
{
	int button = (int)b;
	return pressed[b];
}

bool Input::wasReleased(InputNS::button b)
{
	int button = (int)b;
	return released[b];
}
