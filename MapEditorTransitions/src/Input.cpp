//==========================//
// Input.cpp                //
// Author: Matthew Stephens //
//==========================//
#include "Input.h"
#include <SFML/Window/Mouse.hpp>
#include <fstream>
//=============================
// Constructor()
//=============================
Input::Input(sf::RenderWindow& window):
	window(window)
{
	mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
	prevPos = mousePos;
	charIn = '\0';
	textIn = false;
	backspace = false;

	for (int i = 0; i < 2; i++)
	{
		current[i] = false;
		pressed[i] = false;
		released[i] = false;
	}
}

//=========//
// Methods //
//=========//


bool Input::getTextIn(char& c)
{
	c = charIn;
	return textIn;
}

bool Input::getBackspace()
{
	return backspace;
}


void Input::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
		backspace = true;
	else if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode >= 32 && event.text.unicode <= 126)
		{
			textIn = true;
			charIn = (char)event.text.unicode;
		}
	}
}

void Input::clear()
{
	textIn = false;
	backspace = false;
}


void Input::getInput()
{
	prevPos = mousePos;
	mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

	// Check the left mouse button
	int button = (int)InputNS::LEFT;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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

	// Check the right mouse button
	button = (int)InputNS::RIGHT;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
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

sf::Vector2f Input::getMousePos()
{
	return mousePos;
}

sf::Vector2f Input::getMouseDelta()
{
	return mousePos - prevPos;
}