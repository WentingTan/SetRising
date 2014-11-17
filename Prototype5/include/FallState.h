//==========================//
// FallState.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _FALL_STATE_H_
#define _FALL_STATE_H_

#include <SFML/Graphics.hpp>
#include "PlayerState.h"
#include "Player.h"

class FallState : public PlayerState
{
public:
	// Constructor
	explicit FallState(Player *p);
	// Destructor
	virtual ~FallState() {}

	// Methods
	virtual void enter(float direction);
	virtual void handleInput(Input& input);
	virtual void update(float dt);

private:
	bool move;
};

#endif