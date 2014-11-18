//==========================//
// FallState.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "FallState.h"
#include <SFML/Window/Keyboard.hpp>
#include "Constants.h"

//=============================
// Constructor(Player*)
//=============================
FallState::FallState(Player *p):
	PlayerState(p),
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
void FallState::enter(float direction)
{
	dir = direction;
	//player->setHitboxWidth(64.0f);
	player->setGraphics(PlayerNS::G_AIR, dir);
}

//===============
// handleInput()
//===============
void FallState::handleInput(Input& input)
{

	float x;
	// Transition to jumping state, maintain current direction
	if (input.wasPressed(InputNS::UP))
	{
		if (player->isTouchingLadder(x))
		{
			player->move(x - player->getPosition().x, 1.5f);
			player->setState(PlayerNS::S_CLIMB, dir);
		}
	}

	 // Shooting
    if (input.wasPressed(InputNS::SHOOT))
		player->shoot(dir);


	move = false;
	// Allow horizontal movement while falling
	if (input.isPressed(InputNS::RIGHT))
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
void FallState::update(float dt)
{
	if (move)
		player->move(dir * 200.0f * dt, 0.0f);

	player->move(0.0f, 0.5f * SCREEN_WIDTH * dt);


	if (player->getPosition().y > SCREEN_WIDTH)
	{
		player->setPosition(0.5 * SCREEN_WIDTH, 300.0f);
		player->setState(PlayerNS::S_STAND, PlayerNS::RIGHT);
	}

	// Check for collision with walls
	player->hasHitWall(dir);

	// Check for collision with floors
	// If colliding with a floor, transition to standing state
	if (player->isOnGround())
		player->setState(PlayerNS::S_STAND, dir);

}


