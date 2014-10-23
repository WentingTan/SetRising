//==========================//
// FallState.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "FallState.h"
#include <SFML/Window/Keyboard.hpp>

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
	player->setGraphics(PlayerNS::G_AIR, dir);
}

//===============
// handleInput()
//===============
void FallState::handleInput()
{
	move = false;
	// Allow horizontal movement while falling
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		dir = PlayerNS::RIGHT;
		player->setGraphics(PlayerNS::G_AIR, dir);
		move = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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

	player->move(0.0f, 400.0f * dt);


	if (player->getPosition().y > 800.0f)
	{
		player->setPosition(400.0f, 300.0f);
		player->setState(PlayerNS::S_STAND, PlayerNS::RIGHT);
	}

	// Check for collision with walls
	player->hasHitWall(dir);

	// Check for collision with floors
	// If colliding with a floor, transition to standing state
	if (player->isOnGround())
		player->setState(PlayerNS::S_STAND, dir);

}


