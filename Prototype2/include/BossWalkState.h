//==========================//
// BossWalkState.h              //
// Author: Jinri Hong //
//==========================//
#ifndef _BOSS_WALK_STATE_H_
#define _BOSS_WALK_STATE_H_

#include <SFML/Graphics.hpp>
#include "BossState.h"
#include "Boss.h"

class BossWalkState : public BossState
{
public:
	// Constructor
	BossWalkState(Boss *b, float s);
	// Destructor
	virtual ~BossWalkState() {}

	// Methods
	virtual void enter(float direction);
	virtual void handleInput(Input& input);
	virtual void update(float dt);

private:
	// Animation
	float step;
	float time;
	BossNS::graphics nextFrame;
	BossNS::graphics currFrame;
	BossNS::graphics prevFrame;
};

#endif