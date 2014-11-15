//==========================//
// JumpState.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _JUMP_STATE_H_
#define _JUMP_STATE_H_

#include <SFML/Graphics.hpp>
#include "PlayerState.h"
#include "Player.h"

class JumpState : public PlayerState
{
public:
	// Constructor
	JumpState(Player *p, float maxHeight);
	// Destructor
	virtual ~JumpState() {}

	// Methods
	virtual void enter(float direction);
	virtual void handleInput(Input& input);
	virtual void update(float dt);

private:
	float maxHeight;
	float initialHeight;

	bool move;
};

#endif