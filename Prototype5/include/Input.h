//==========================//
// Input.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _INPUT_H_
#define _INPUT_H_

#include <SFML/Window/Keyboard.hpp>

namespace InputNS
{
	enum button
	{
		LEFT = 0,
		RIGHT = 1,
		UP = 2,
		DOWN = 3,
		JUMP = 4,
		SHOOT = 5,
		SEL_LASER = 6,
		SEL_FREEZE = 7
	};

	const int NUM_BUTTONS = 8;
};

class Input
{
public:
	// Constructor
	Input();
	// Destructor
	~Input() {}

	// Accessors
	bool isPressed(InputNS::button button);
	bool wasPressed(InputNS::button button);
	bool wasReleased(InputNS::button button);

	// Methods
	void getInput();

private:
	bool current[InputNS::NUM_BUTTONS];
	bool pressed[InputNS::NUM_BUTTONS];
	bool released[InputNS::NUM_BUTTONS];
};

#endif