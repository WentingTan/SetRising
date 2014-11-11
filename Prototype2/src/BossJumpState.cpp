//==========================//
// JumpState.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "BossJumpState.h"
#include <SFML/Window/Keyboard.hpp>

//=============================
// Constructor(Boss*, float)
//=============================
BossJumpState::BossJumpState(Boss *b, float maxHeight, float s) :
BossState(b),
step(s),
time(0.0f),
maxHeight(maxHeight),
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
void BossJumpState::enter(float direction)
{
	dir = direction;
	boss->setHitboxWidth(64.0f);
	initialHeight = boss->getPosition().y;
	boss->setGraphics(BossNS::G_JUMP0, dir);
}

//===============
// handleInput()
//===============
void BossJumpState::handleInput(Input& input)
{

	move = false;
	/*
	// Transition to falling state if jump button no longer pressed
	if (input.wasReleased(InputNS::JUMP))
	{
		boss->setState(BossNS::S_FALL, dir);
	}
	*/


	float x;
	// Transition to jumping state, maintain current direction
	


	// Transition back to standing state if the arrow key corresponding to the current
	// direction is no longer being pressed
	if (input.isPressed(InputNS::RIGHT))
	{
		dir = BossNS::RIGHT;
		//boss->setGraphics(BossNS::G_JUMP1, dir);
		move = true;
	}
	else if (input.isPressed(InputNS::LEFT))
	{
		dir = BossNS::LEFT;
	//	boss->setGraphics(BossNS::G_JUMP1, dir);
		move = true;
	}
}

//===============
// update(float)
//===============
void BossJumpState::update(float dt)
{

	time += dt;

	// Walking Animation
	if (time > step)
	{
		prevFrame = currFrame;
		currFrame = nextFrame;
		// Update the frame of the animation 
		boss->setGraphics(currFrame, dir);

		// Update the next frame of animation
		switch (currFrame)
		{
		case BossNS::G_JUMP0:
			nextFrame = BossNS::G_JUMP1;
			break;
		case BossNS::G_JUMP1:
			nextFrame = BossNS::G_JUMP2;
			break;
		case BossNS::G_JUMP2:
			nextFrame = BossNS::G_JUMP3;
			break;
		default:
			nextFrame = BossNS::G_JUMP0;
			break;
		}

		time = 0.0f;
	}


	if (move)
		boss->move(dir * 200.0f * dt, 0.0f);

	float jumpedHeight = initialHeight - boss->getPosition().y;

	if (boss->hasHitCeiling())
	{
		boss->setState(BossNS::S_FALL, dir);
	}
	else if (jumpedHeight > maxHeight)
	{
		boss->setPosition(boss->getPosition().x, initialHeight - maxHeight);
		boss->setState(BossNS::S_FALL, dir);
	}
	else
	{
		if (jumpedHeight > 0.85 * maxHeight)
		{
			boss->move(0.0f, -150.0f * dt);
		}
		else if (jumpedHeight > 0.60 * maxHeight)
		{
			boss->move(0.0f, -275.0f * dt);
		}
		else
			boss->move(0.0f, -400.0f * dt);
	}

	// Check for collision with walls
	boss->hasHitWall(dir);
}


