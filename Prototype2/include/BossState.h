//==========================//
// BossState.h            //
// Author: Jinri Hong //
//==========================//
#ifndef _BOSS_STATE_H_
#define _BOSS_STATE_H_

#include <SFML/Graphics.hpp>
#include "Input.h"

class Boss;

class BossState
{
public:
	// Constructor
	BossState(Boss *k) { boss = k; }
	// Destructor
	virtual ~BossState() {}

	// Methods
	virtual void enter(float direction) = 0;
	virtual void handleInput(Input& input) = 0;
	virtual void update(float dt) = 0;

protected:
	Boss *boss;
	float dir;
};

#endif