//==========================//
// TextField.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _TEXT_FIELD_H_
#define _TEXT_FIELD_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "Input.h"

class TextField
{
public:
	// Constructor
	TextField(const sf::Font& f, std::string name, int charSize, int charLimit);

	// Accessors
	std::string getEnteredText();

	// Mutators
	void setPosition(sf::Vector2f p);
	void setTextColor(sf::Color color);
	void setTextAreaOutline(int thickness, sf::Color color);
	void setEnteredText(std::string text);
	void setActive(bool a);

	// Methods
	void handleInput(Input *input);
	void draw(sf::RenderWindow& window);

private:
	sf::Text name;
	sf::Text entered;

	sf::RectangleShape textArea;

	sf::RectangleShape cursor;

	sf::Vector2f pos;
	float padding;
	int charLimit;


	int charSize;

	bool active;

	// Helpers
	void updatePositions();
	void addChar(char c);
	void deleteChar();

};

#endif