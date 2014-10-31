//==========================//
// JumpState.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _BOSS_JUMP_STATE_H
#define _BOSS_JUMP_STATE_H

#include <SFML/Graphics.hpp>
#include "BossState.h"
#include "Boss.h"

class BossJumpState : public BossState
{
public:
	// Constructor
	BossJumpState(Boss *b, float maxHeight);
	// Destructor
	virtual ~BossJumpState() {}

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