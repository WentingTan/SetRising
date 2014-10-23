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
	player->setGraphics(PlayerNS::G_STAND, dir);

}

//===============
// handleInput()
//===============
void StandState::handleInput()
{
	// Transition to jumping state, maintain current direction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player->setState(PlayerNS::S_JUMP, dir);
	}
	// Transition to walking state, direction = right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player->setState(PlayerNS::S_WALK, PlayerNS::RIGHT);
	}
	// Transition to walking state, direction = left
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player->setState(PlayerNS::S_WALK, PlayerNS::LEFT);
	}
}

//==========
// update()
//==========
void StandState::update(float dt)
{
	// Do nothing
}


