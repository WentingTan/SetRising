//==========================//
// StandState.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _BOSS_STAND_STATE_H_
#define _BOSS_STAND_STATE_H_

#include <SFML/Graphics.hpp>
#include "BossState.h"
#include "Boss.h"

class BossStandState : public BossState
{
public:
	// Constructor
	explicit BossStandState(Boss *k);
	// Destructor
	virtual ~BossStandState() {}

	// Methods
	virtual void enter(float direction);
	virtual void handleInput(Input& input);
	virtual void update(float dt);

private:
};

#endif