//==========================//
// StandState.cpp           //
// Author: Matthew Stephens //
//==========================//
#include "BossStandState.h"
#include <SFML/Window/Keyboard.hpp>


#include <fstream>

//======================
// Constructor(Player*)
//======================
BossStandState::BossStandState(Boss *k) :
BossState(k)
{
	// Do nothing
}

//=========//
// Methods //
//=========//

//==============
// enter(float)
//==============
void BossStandState::enter(float direction)
{
	dir = direction;
	boss->setHitboxWidth(130.0f);
	boss->isOnGround();
	boss->setGraphics(BossNS::G_STAND, dir);

}

//===============
// handleInput()
//===============
void BossStandState::handleInput(Input& input)
{
	float x;


	if (input.isPressed(InputNS::DOWN))
	{
		
			boss->setState(BossNS::S_DIG, dir);
		
	}

	if (input.wasPressed(InputNS::JUMP))
	{
		//player->move(0.0f, -180.0f * dt);
		boss->setState(BossNS::S_JUMP, dir);
	}

	// Transition to walking state, direction = right
	else if (input.isPressed(InputNS::RIGHT))
	{
		boss->setState(BossNS::S_WALK, BossNS::RIGHT);
	}
	// Transition to walking state, direction = left
	else if (input.isPressed(InputNS::LEFT))
	{
		boss->setState(BossNS::S_WALK, BossNS::LEFT);
	}
}

//==========
// update()
//==========
void BossStandState::update(float dt)
{
	// Do nothing
}


