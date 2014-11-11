//==========================//
// BossWalkState.cpp        //
// Author: Jinri Hong //
//==========================//
#include "BossWalkState.h"
//#include "Boss.h"
#include <SFML/Window/Keyboard.hpp>

//=============================
// Constructor(Boss*, float)
//=============================
BossWalkState::BossWalkState(Boss *b, float s) :
BossState(b),
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
// Sets up the parameters for the walking animation. Sets the Boss's graphic
// to the initial walking graphic (BossNS::G_WALK0).
//=============================================================================
void BossWalkState::enter(float direction)
{
	time = 0.0f;
	dir = direction;
	boss->setHitboxWidth(138.0f);

	currFrame = BossNS::G_WALK0;
	nextFrame = BossNS::G_WALK1;
	boss->setGraphics(currFrame, dir);
}

//===============
// handleInput()
//===============
void BossWalkState::handleInput(Input& input)
{
	float x;
	// Transition to jumping state, maintain current direction


	if (input.isPressed(InputNS::DOWN))
	{
		boss->setState(BossNS::S_DIG, dir);
		
	}

	if (input.wasPressed(InputNS::JUMP))
	{
		//player->move(0.0f, -180.0f * dt);
		boss->setState(BossNS::S_JUMP, dir);
	}



	// Transition back to standing state if the arrow key corresponding to the current
	// direction is no longer being pressed
	else if (dir == BossNS::RIGHT && !input.isPressed(InputNS::RIGHT))
	{
		boss->setState(BossNS::S_STAND, dir);
	}
	else if (dir == BossNS::LEFT && input.wasReleased(InputNS::LEFT))
	{
		boss->setState(BossNS::S_STAND, dir);
	}
}

//===============
// update(float)
//===============
void BossWalkState::update(float dt)
{
	// Add the frame time to the animation timer
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
		case BossNS::G_WALK0:
			nextFrame = BossNS::G_WALK1;
			break;
		case BossNS::G_WALK1:
			nextFrame = BossNS::G_WALK2;
			break;
		default:
			nextFrame = BossNS::G_WALK0;
			break;
		}

		time = 0.0f;
	}

	// Move the player
	// HERE 200 IS PLAYER SPEED IN PIXELS/SECOND
	boss->move(dir * 200.0f * dt, 0.0f);

	// Check for collision with walls
	boss->hasHitWall(dir);

	// Check for collision with floor
	// If no collision, transition to FallState
	
}


