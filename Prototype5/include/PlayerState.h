//==========================//
// PlayerState.h            //
// Author: Matthew Stephens //
//==========================//
#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include <SFML/Graphics.hpp>
#include "Input.h"

class Player;

class PlayerState
{
public:
	// Constructor
	PlayerState(Player *p) { player = p; }
	// Destructor
	virtual ~PlayerState() {}

	// Methods
	virtual void enter(float direction) = 0;
	virtual void handleInput(Input& input) = 0;
	virtual void update(float dt) = 0;

protected:
	Player *player;
	float dir;
};

#endif