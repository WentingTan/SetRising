//==========================//
// BossDigState.h              //
// Author: Jinri Hong //
//==========================//
#ifndef _BOSS_DIG_STATE_H_
#define _BOSS_DIG_STATE_H_

#include <SFML/Graphics.hpp>
#include "BossState.h"
#include "Boss.h"

class BossDigState : public BossState
{
public:
	// Constructor
	BossDigState(Boss *b, float s, float m);
	// Destructor
	virtual ~BossDigState() {}

	// Methods
	virtual void enter(float direction);
	virtual void handleInput(Input& input);
	virtual void update(float dt);

private:
	// Animation
	float maxHeight;
	float initialHeight;
	bool falling;
	bool land;

	float step;
	float time;
	BossNS::graphics nextFrame;
	BossNS::graphics currFrame;
	BossNS::graphics prevFrame;
};

#endif