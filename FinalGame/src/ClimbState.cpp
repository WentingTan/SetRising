//==========================//
// ClimbState.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "ClimbState.h"
//#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

//=============================
// Constructor(Player*, float)
//=============================
ClimbState::ClimbState(Player *p, float s):
	PlayerState(p),
	step(s),
	time(0.0f)
{
	// Do nothing
}

//=========//
// Methods //
//=========//

//=============================================================================
// enter(float)
// Sets up the parameters for the walking animation. Sets the Player's graphic
// to the initial walking graphic (PlayerNS::G_WALK0).
//=============================================================================
void ClimbState::enter(float direction)
{
	time = 0.0f;
	dir = direction;

	moveUp = moveDown = false;

	//player->setHitboxWidth(48.0f);

	currFrame = PlayerNS::G_CLIMB0;
	player->setGraphics(PlayerNS::G_CLIMB0, dir);
}

//===============
// handleInput(Input&)
//===============
void ClimbState::handleInput(Input& input)
{
	moveUp = moveDown = false;
	// Climb up
	if (input.isPressed(InputNS::UP))
	{
		//player->move(0.0f, -180.0f * dt);
		moveUp = true;
	}

	// Climb down
	if (input.isPressed(InputNS::DOWN))
	{
		//player->move(0.0f, 180.0f * dt);
		moveDown = true;
	}

	if (input.wasPressed(InputNS::JUMP))
	{
		player->setState(PlayerNS::S_FALL, dir);
	}

}

//===============
// update(float)
//===============
void ClimbState::update(float dt)
{
	if (moveUp)
		player->move(0.0f, -180.0f * dt);
	else if (moveDown)
		player->move(0.0f, 180.0f * dt);
	if (moveUp || moveDown)
	{
		// Add the frame time to the animation timer
		time += dt;

		// Walking Animation
		if (time > step)
		{
			currFrame = currFrame == PlayerNS::G_CLIMB0 ? PlayerNS::G_CLIMB1 : PlayerNS::G_CLIMB0;
			// Update the frame of the animation 
			player->setGraphics(currFrame, dir);
			time = 0.0f;
		}
	}

	float x;
	//if (moveUp && (!player->isTouchingLadder(x) && !player->isOnLadderTop(x)))
	if (moveUp && !player->isTouchingLadder(x))
	{
		player->move(0.0f, -1.0f * TileNS::SIZE + 1.0f);
		//player->isOnGround();
		player->setState(PlayerNS::S_STAND, dir);
	}
	else if (moveDown && player->isOnGround())
		player->setState(PlayerNS::S_STAND, dir);

}


