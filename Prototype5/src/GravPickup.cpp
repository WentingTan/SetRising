//==========================//
// GravPickup.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "GravPickup.h"
#include "Constants.h"
#include "AlphaOscillator.h"

GravPickup::GravPickup():
	Pickup()
{
	// Do nothing
}

GravPickup::~GravPickup()
{
	// Do nothing
}

//===========//
// Accessors //
//===========//

//=============================================================================================
// GravPickup::activate(sf::Vector2f,int,sf::Vector2i)
// 
//=============================================================================================
void GravPickup::activate(sf::Vector2f pos)
{
	sprite.setColor(sf::Color::White);

	// Set the sprite's position
	sprite.setPosition(pos);

	// Set the hitbox
	hitbox = sprite.getGlobalBounds();

	// Set the active flag to true
	active = true;

	time = 0.0f;
	fadeBlinker.reset();
}

//================================================================================
// HealthPickup::swap(HealthPickup&)
// Swaps all data members between this pickup and the pickup passed by reference.
//================================================================================
void GravPickup::copy(GravPickup& gp)
{
	texture = gp.texture;
	sprite = gp.sprite;
	hitbox = gp.hitbox;
	active = gp.active;
	time = gp.time;
	fadeBlinker = gp.fadeBlinker;
}

