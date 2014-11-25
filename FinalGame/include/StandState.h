//==========================//
// StandState.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _STAND_STATE_H_
#define _STAND_STATE_H_

#include <SFML/Graphics.hpp>
#include "PlayerState.h"
#include "Player.h"

class StandState : public PlayerState
{
public:
	// Constructor
	explicit StandState(Player *p);
	// Destructor
	virtual ~StandState() {}

	// Methods
	virtual void enter(float direction);
	virtual void handleInput(Input& input);
	virtual void update(float dt);

private:
};

#endif