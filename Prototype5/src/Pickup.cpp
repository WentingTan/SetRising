//==========================//
// Pickup.cpp               //
// Author: Matthew Stephens //
//==========================//
#include "Pickup.h"
#include "Constants.h"
#include "AlphaOscillator.h"

Pickup::Pickup():
	Entity(),
	fadeBlinker(FD_ALPHA_HI, FD_ALPHA_LO, FD_CYCLE)
{
	// Do nothing
}

Pickup::~Pickup()
{
	// Do nothing
}

//===========//
// Accessors //
//===========//

//=======================================
// Pickup::init()
// Sets the sprite's texture and origin.
//=======================================
void Pickup::init()
{
	sprite.setTexture(*texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
}


//===============================
// Pickup::deactivate()
// Deactivates the Pickup.
//===============================
void Pickup::deactivate()
{
	active = false;
}


//=======================================================================
// GravPickup::update(float)
//
//=======================================================================
bool Pickup::update(float dt)
{
	time += dt;

	if (time > TIME_TILL_FADE + FADE_TIME)
		return true;
	else if (time > TIME_TILL_FADE)
	{
		fadeBlinker.update(dt);
		sprite.setColor(sf::Color(255, 255, 255, fadeBlinker.getAlpha()));
	}
	return false;
}

