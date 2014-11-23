//==========================//
// RadioButton.h            //
// Author: Matthew Stephens //
//==========================//
#ifndef _RADIO_BUTTON_H_
#define _RADIO_BUTTON_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "Input.h"

class RadioButton
{
public:
	// Constructor
	RadioButton(const sf::Font& f, int numOpts);

	// Accessors
	int getSelected();

	void setSelected(int sel);


	void init();

	// Mutators
	void setPosition(sf::Vector2f p);
	void setTitle(std::string str, int charSize);
	void setOption(std::string str, int charSize, int index);
	
	void update(float dt);
	

	// Methods
	void handleInput(Input *input);
	void draw(sf::RenderWindow& window);

private:
	int nOptions;
	sf::Text title;
	//sf::CircleShape selCircle;
	sf::CircleShape *optButtons;
	sf::Text *optNames;
	int selected;
	sf::Font font;

	sf::Vector2f pos;

	sf::Color textActive;
	sf::Color textInactive;

	// Helpers
	void updatePositions();
};

#endif