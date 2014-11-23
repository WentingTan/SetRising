//==========================//
// Button.cpp               //
// Author: Matthew Stephens //
//==========================//
#include "Button.h"
#include <fstream>

// Accessors

Button::Button()
{
	clicked = false;
}

bool Button::wasClicked()
{
	return clicked;
}

// Mutators

void Button::setPosition(sf::Vector2f p)
{
	pos = p;
	updatePositions();
}

void Button::setSize(sf::Vector2f size)
{
	buttonRect.setSize(size);
}

void Button::setText(sf::Font& f, std::string str, int charSize)
{
	text.setFont(f);
	text.setString(str);
	text.setCharacterSize(charSize);
}

void Button::setTextColors(sf::Color active, sf::Color inactive)
{
	textActive = active;
	textInactive = inactive;
}

void Button::setButtonColors(sf::Color active, sf::Color inactive, sf::Color mouseOver, sf::Color clicked)
{
	buttonActive = active;
	buttonInactive = inactive;
	buttonMouse = mouseOver;
	buttonClick = clicked;
}

void Button::setOutline(int thickness, sf::Color color)
{
	buttonRect.setOutlineThickness(thickness);
	buttonRect.setOutlineColor(color);
}

void Button::setActive(bool a)
{
	active = a;
	if (active)
	{
		buttonRect.setFillColor(buttonActive);
		text.setColor(textActive);
	}
	else
	{
		buttonRect.setFillColor(buttonInactive);
		text.setColor(textInactive);
	}
}

// Methods

void Button::handleInput(Input *input)
{
	clicked = false;

	if (!active)
		return;

	sf::Vector2f mousePos = input->getMousePos();

	if (buttonRect.getGlobalBounds().contains(mousePos))
	{
		buttonRect.setFillColor(buttonMouse);
		if (input->wasPressed(InputNS::LEFT))
		{
			buttonRect.setFillColor(buttonClick);
			clicked = true;
		}
	}
	else
		buttonRect.setFillColor(buttonActive);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(buttonRect);
	window.draw(text);
}

// Helpers

void Button::updatePositions()
{
	// Button's origin is top left corner
	buttonRect.setOrigin(0.0f, 0.0f);
	buttonRect.setPosition(pos);

	// Calculate center of the button
	sf::FloatRect bounds = buttonRect.getGlobalBounds();
	sf::Vector2f center;
	center.x = bounds.left + bounds.width / 2.0f;
	center.y = bounds.top + bounds.height / 2.0f;

	// Text's origin is its center
	bounds = text.getLocalBounds();
	text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	text.setPosition(center);
}