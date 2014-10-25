//==========================//
// ClimbState.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _CLIMB_STATE_H_
#define _CLIMB_STATE_H_

#include <SFML/Graphics.hpp>
#include "PlayerState.h"
#include "Player.h"

class ClimbState : public PlayerState
{
public:
	// Constructor
	ClimbState(Player *p, float s);
	// Destructor
	virtual ~ClimbState() {}

	// Methods
	virtual void enter(float direction);
	virtual void handleInput(Input& input);
	virtual void update(float dt);

private:
	// Animation
	float step;
	float time;
	PlayerNS::graphics currFrame;
	bool moveUp;
	bool moveDown;
};

#endif