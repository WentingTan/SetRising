//==========================//
// BossWalkState.cpp        //
// Author: Jinri Hong //
//==========================//
#include "BossDigState.h"
//#include "Boss.h"
#include <SFML/Window/Keyboard.hpp>

//=============================
// Constructor(Boss*, float)
//=============================
BossDigState::BossDigState(Boss *p, float s, float m) :
BossState(p),
step(s),
time(0.0f),
maxHeight(m)
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
void BossDigState::enter(float direction)
{
	time = 0.0f;
	dir = direction;
	boss->setHitboxWidth(138.0f);
	initialHeight = boss->getPosition().y;
	falling = false;
	land = false;

	currFrame = BossNS::G_DIG0;
	nextFrame = BossNS::G_DIG1;
	boss->setGraphics(currFrame, dir);
}

//===============
// handleInput()
//===============
void BossDigState::handleInput(Input& input)
{
	float x;
	// Transition to jumping state, maintain current direction


	if (input.isPressed(InputNS::DOWN))
	{
		boss->setState(BossNS::S_DIG, dir);

	}
	if (input.isPressed(InputNS::UP))
	{
		boss->setState(BossNS::S_STAND, dir);

		//boss->setState(BossNS::S_DIG, dir);

	}

	if (input.wasPressed(InputNS::JUMP))
	{
		//player->move(0.0f, -180.0f * dt);
		boss->setState(BossNS::S_STAND, dir);
	}





	
}

//===============
// update(float)
//===============
void BossDigState::update(float dt)
{
	if (land){
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

			case BossNS::G_DIG0:
				nextFrame = BossNS::G_DIG1;
				break;
			case BossNS::G_DIG1:
				nextFrame = BossNS::G_DIG2;
				break;
			
			default:
				break;
			}


			time = 0.0f;




		}
	}
	else{
		// Move the player
		// HERE 200 IS PLAYER SPEED IN PIXELS/SECOND
		float jumpedHeight = initialHeight - boss->getPosition().y;


		if (jumpedHeight > maxHeight)
		{
			boss->setPosition(boss->getPosition().x, initialHeight - maxHeight);
			boss->setState(BossNS::S_DIG, dir);
			falling = true;

		}
		else
		{
			if (falling){
				boss->move(0.0f, 400.0f * dt);

			}
			else{
				boss->move(0.0f, -400.0f * dt);
			}
		}

		// Check for collision with walls
		if (boss->hasHitWall(dir)){
			falling = false;
			boss->setGraphics(BossNS::G_DIG1, dir);
			//		boss->setState(BossNS::S_STAND, dir);
			land = true;
		}
	}
	// Check for collision with floor

	// If no collision, transition to FallState

}


