//==========================//
// HealthPickup.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "HealthPickup.h"
#include "AlphaOscillator.h"
#include "Constants.h"

HealthPickup::HealthPickup():
	Pickup()
{
	// Do nothing
}

HealthPickup::~HealthPickup()
{
	// Do nothing
}

//===========//
// Accessors //
//===========//

//=========================================
// HealthPickup::getHealth()
// Returns the health value of the pickup.
//=========================================
float HealthPickup::getHealth() const
{
	return health;
}

//=========================================================================================
// HealthPickup::activate(sf::Vector2f,int,sf::Vector2i)
// Sets the scale factor and position of the sprite and the amount of health received from 
// the pickup based on the 'size' parameter. Sets the pickup to active.
//=========================================================================================
void HealthPickup::activate(sf::Vector2f pos, int type)
{
	// Set the health value and scale of the sprite depending on the 'size'
	// of the pickup
	if (type == SM_HEALTH)
	{
		health = SM_HEALTH_VAL;
		sprite.setScale(1.0f, 1.0f);
	}
	else
	{
		health = LG_HEALTH_VAL;
		sprite.setScale(2.0f, 2.0f);
	}
	sprite.setColor(sf::Color::White);

	// Set the sprite's position
	sprite.setPosition(pos);

	// Set the hitbox
	hitbox = sprite.getGlobalBounds();

	// Set the active flag to true
	active = true;

	fadeBlinker.reset();
}

void HealthPickup::copy(HealthPickup& hp)
{
	texture = hp.texture;
	sprite = hp.sprite;
	hitbox = hp.hitbox;
	active = hp.active;
	time = hp.time;
	fadeBlinker = hp.fadeBlinker;
	health = hp.health;
}

