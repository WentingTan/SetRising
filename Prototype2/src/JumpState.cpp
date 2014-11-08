//==========================//
// JumpState.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "JumpState.h"
#include <SFML/Window/Keyboard.hpp>

//=============================
// Constructor(Player*, float)
//=============================
JumpState::JumpState(Player *p, float maxHeight):
	PlayerState(p),
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
void JumpState::enter(float direction)
{
	dir = direction;
	player->setHitboxWidth(64.0f);
	initialHeight = player->getPosition().y;
	player->setGraphics(PlayerNS::G_AIR, dir);
}

//===============
// handleInput()
//===============
void JumpState::handleInput(Input& input)
{
	move = false;
	// Transition to falling state if jump button no longer pressed
	if (input.wasReleased(InputNS::JUMP))
	{
		player->setState(PlayerNS::S_FALL, dir);
	}



	float x;
	// Transition to jumping state, maintain current direction
	if (input.wasPressed(InputNS::UP))
	{
		if (player->isTouchingLadder(x))
		{
			player->move(x - player->getPosition().x, 0.5f);
			player->setState(PlayerNS::S_CLIMB, dir);
		}
	}


	 // Shooting
    if (input.wasPressed(InputNS::SHOOT))
	{
		player->shoot(dir);
	}

	// Transition back to standing state if the arrow key corresponding to the current
	// direction is no longer being pressed
	else if (input.isPressed(InputNS::RIGHT))
	{
		dir = PlayerNS::RIGHT;
		player->setGraphics(PlayerNS::G_AIR, dir);
		move = true;
	}
	else if (input.isPressed(InputNS::LEFT))
	{
		dir = PlayerNS::LEFT;
		player->setGraphics(PlayerNS::G_AIR, dir);
		move = true;
	}
}

//===============
// update(float)
//===============
void JumpState::update(float dt)
{
	if (move)
		player->move(dir * 200.0f * dt, 0.0f);

	float jumpedHeight = initialHeight - player->getPosition().y;

	if (player->hasHitCeiling())
	{
		player->setState(PlayerNS::S_FALL, dir);
	}
	else if (jumpedHeight > maxHeight)
	{
		player->setPosition(player->getPosition().x, initialHeight - maxHeight);
		player->setState(PlayerNS::S_FALL, dir);
	}
	else
	{
		if (jumpedHeight > 0.85 * maxHeight)
		{
			player->move(0.0f, -150.0f * dt);
		}
		else if (jumpedHeight > 0.60 * maxHeight)
		{
			player->move(0.0f, -275.0f * dt);
		}
		else
			player->move(0.0f, -400.0f * dt);
	}

	// Check for collision with walls
	player->hasHitWall(dir);
}


