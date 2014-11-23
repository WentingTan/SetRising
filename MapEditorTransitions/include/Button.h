//==========================//
// Button.h                 //
// Author: Matthew Stephens //
//==========================//
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "Input.h"

class Button
{
public:
	// Constructor
	Button();

	// Accessors
	bool wasClicked();

	// Mutators
	void setPosition(sf::Vector2f p);
	void setSize(sf::Vector2f size);
	void setText(sf::Font& f, std::string str, int charSize);
	void setTextColors(sf::Color active, sf::Color inactive);
	void setButtonColors(sf::Color active, sf::Color inactive, sf::Color mouseOver, sf::Color clicked);
	void setOutline(int thickness, sf::Color color);
	void setActive(bool a);

	// Methods
	void handleInput(Input *input);
	void draw(sf::RenderWindow& window);

private:
	sf::Text text;
	sf::RectangleShape buttonRect;
	sf::Vector2f pos;
	bool active;
	bool clicked;

	sf::Color buttonActive;
	sf::Color buttonInactive;
	sf::Color buttonMouse;
	sf::Color buttonClick;

	sf::Color textActive;
	sf::Color textInactive;

	// Helpers
	void updatePositions();
};

#endif