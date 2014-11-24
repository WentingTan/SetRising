//==========================//
// StandState.cpp           //
// Author: Matthew Stephens //
//==========================//
#include "StandState.h"
#include <SFML/Window/Keyboard.hpp>


#include <fstream>

//======================
// Constructor(Player*)
//======================
StandState::StandState(Player *p):
	PlayerState(p)
{
	// Do nothing
}

//=========//
// Methods //
//=========//

//==============
// enter(float)
//==============
void StandState::enter(float direction)
{
	dir = direction;
	//player->setHitboxWidth(64.0f);
	player->isOnGround();
	player->setGraphics(PlayerNS::G_STAND, dir);

}

//===============
// handleInput()
//===============
void StandState::handleInput(Input& input)
{
	float x;
	
	if (input.isPressed(InputNS::UP))
	{
		if (player->isTouchingLadder(x))
		{
			player->move(x - player->getPosition().x, 2.5f);
			player->setState(PlayerNS::S_CLIMB, dir);
		}
	}

	if (input.isPressed(InputNS::DOWN))
	{
		if (player->isOnLadderTop(x))
		{
			player->move(x - player->getPosition().x, 0.5f);
			player->setState(PlayerNS::S_CLIMB, dir);
		}
	}

	if (input.wasPressed(InputNS::JUMP))
	{
		//player->move(0.0f, -180.0f * dt);
		player->setState(PlayerNS::S_JUMP, dir);
	}
	// Transition to walking state, direction = right
	else if (input.isPressed(InputNS::RIGHT))
	{
		player->setState(PlayerNS::S_WALK, D_RIGHT);
	}
	// Transition to walking state, direction = left
	else if (input.isPressed(InputNS::LEFT))
	{
		player->setState(PlayerNS::S_WALK, D_LEFT);
	}

    // Shooting
   // if (input.wasPressed(InputNS::SHOOT))
	//{
		//player->shoot(dir);
	//}
}

//==========
// update()
//==========
void StandState::update(float dt)
{
	if (!player->isOnGround())
		player->setState(PlayerNS::S_FALL, dir);

	// Check for collision with walls
	player->hasHitWall(dir);
}


