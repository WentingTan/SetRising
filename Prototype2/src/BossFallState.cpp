//==========================//
// BossState.cpp        //
// Author: Jinri Hong //
//==========================//
#include "BossFallState.h"
#include <SFML/Window/Keyboard.hpp>

//=============================
// Constructor(Player*)
//=============================
BossFallState::BossFallState(Boss *b) :
BossState(b),
move(false)
{
	// Do nothing
}

//=========//
// Methods //
//=========//

//==============
// enter(float)
//==============
void BossFallState::enter(float direction)
{
	dir = direction;
	boss->setHitboxWidth(100.0f);
	boss->setGraphics(BossNS::G_STAND, dir);
}

//===============
// handleInput()
//===============
void BossFallState::handleInput(Input& input)
{

	float x;
	// Transition to jumping state, maintain current direction



	move = false;
	// Allow horizontal movement while falling
	if (input.isPressed(InputNS::RIGHT))
	{
		dir = BossNS::RIGHT;
		boss->setGraphics(BossNS::G_STAND, dir);
		move = true;
	}
	else if (input.isPressed(InputNS::LEFT))
	{
		dir = BossNS::LEFT;
		boss->setGraphics(BossNS::G_STAND, dir);
		move = true;
	}
}

//===============
// update(float)
//===============
void BossFallState::update(float dt)
{
	if (move)
		boss->move(dir * 200.0f * dt, 0.0f);

	boss->move(0.0f, 400.0f * dt);


	if (boss->getPosition().y > 800.0f)
	{
		boss->setPosition(400.0f, 300.0f);
		boss->setState(BossNS::S_STAND, BossNS::RIGHT);
	}

	// Check for collision with walls
	boss->hasHitWall(dir);

	// Check for collision with floors
	// If colliding with a floor, transition to standing state
	if (boss->isOnGround())
		boss->setState(BossNS::S_STAND, dir);

}


