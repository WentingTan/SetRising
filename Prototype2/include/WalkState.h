//==========================//
// WalkState.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _WALK_STATE_H_
#define _WALK_STATE_H_

#include <SFML/Graphics.hpp>
#include "PlayerState.h"
#include "Player.h"

class WalkState : public PlayerState
{
public:
	// Constructor
	WalkState(Player *p, float s);
	// Destructor
	virtual ~WalkState() {}

	// Methods
	virtual void enter(float direction);
	virtual void handleInput(Input& input);
	virtual void update(float dt);

private:
	// Animation
	float step;
	float time;
	PlayerNS::graphics nextFrame;
	PlayerNS::graphics currFrame;
	PlayerNS::graphics prevFrame;
};

#endif