//==========================//
// Input.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _INPUT_H_
#define _INPUT_H_

#include <SFML/Graphics.hpp>

namespace InputNS
{
	enum button
	{
		LEFT = 0,
		RIGHT = 1
	};

	const int NUM_BUTTONS = 5;
};

class Input
{
public:
	// Constructor
	Input(sf::RenderWindow& window);
	// Destructor
	~Input() {}

	void handleEvent(sf::Event event);

	// Accessors
	bool isPressed(InputNS::button b);
	bool wasPressed(InputNS::button b);
	bool wasReleased(InputNS::button b);
	sf::Vector2f getMousePos();
	sf::Vector2f getMouseDelta();



	void clear();


	bool getTextIn(char& c);
	bool getBackspace();




	// Methods
	void getInput();

private:
	sf::RenderWindow& window;

	bool current[2];
	bool pressed[2];
	bool released[2];
	char charIn;
	bool textIn;
	bool backspace;

	sf::Vector2f mousePos;
	sf::Vector2f prevPos;
};

#endif