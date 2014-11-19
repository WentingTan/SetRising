//==========================//
// WalkState.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "WalkState.h"
//#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

//=============================
// Constructor(Player*, float)
//=============================
WalkState::WalkState(Player *p, float s):
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
void WalkState::enter(float direction)
{
	time = 0.0f;
	dir = direction;
	//player->setHitboxWidth(64.0f);

	currFrame = PlayerNS::G_WALK0;
	nextFrame = PlayerNS::G_WALK1;
	player->setGraphics(currFrame, dir);
}

//===============
// handleInput()
//===============
void WalkState::handleInput(Input& input)
{
	float x;
	// Transition to jumping state, maintain current direction
	if (input.isPressed(InputNS::UP))
	{
		if (player->isTouchingLadder(x))
		{
			player->move(x - player->getPosition().x, -2.5f);
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


     // Shooting
   // if (input.wasPressed(InputNS::SHOOT))
	//{
		//player->shoot(dir);
	//}



	// Transition back to standing state if the arrow key corresponding to the current
	// direction is no longer being pressed
	else if (dir == D_RIGHT && !input.isPressed(InputNS::RIGHT))
	{
		player->setState(PlayerNS::S_STAND, dir);
	}
	else if (dir == D_LEFT && !input.isPressed(InputNS::LEFT))
	{
		player->setState(PlayerNS::S_STAND, dir);
	}
}

//===============
// update(float)
//===============
void WalkState::update(float dt)
{
	// Add the frame time to the animation timer
	time += dt;

	// Walking Animation
	if (time > step)
	{
		int currentF = ((int)currFrame + 1) %  10;
		if (currentF == 0)
			currentF = 2;
		
		currFrame = (PlayerNS::graphics)currentF;
		// Update the frame of the animation 
		player->setGraphics(currFrame, dir);



		/*
		// Update the next frame of animation
		switch (currFrame)
		{
		case PlayerNS::G_WALK0:
			nextFrame = PlayerNS::G_WALK1;
			break;
		case PlayerNS::G_WALK1:
			nextFrame = PlayerNS::G_WALK2;
			break;
		case PlayerNS::G_WALK2:
			if (prevFrame == PlayerNS::G_WALK1)
				nextFrame = PlayerNS::G_WALK3;
			else
				nextFrame = PlayerNS::G_WALK1;
			break;
		case PlayerNS::G_WALK3:
			nextFrame = PlayerNS::G_WALK2;
			break;
		default:
			break;
		}
		*/

		time = 0.0f;
	}

	// Move the player
	// HERE 200 IS PLAYER SPEED IN PIXELS/SECOND
	player->move(dir * 200.0f * dt, 0.0f);

	// Check for collision with walls
	player->hasHitWall(dir);

	// Check for collision with floor
	// If no collision, transition to FallState
	if (!player->isOnGround())
		player->setState(PlayerNS::S_FALL, dir);
}


