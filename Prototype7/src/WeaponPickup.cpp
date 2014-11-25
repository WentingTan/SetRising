//==========================//
// WeaponPickup.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "WeaponPickup.h"
#include "EventManager.h"
#include <fstream>
WeaponPickup::WeaponPickup():
	Pickup()
{
	// Do nothing
}

WeaponPickup::~WeaponPickup()
{
	// Do nothing
}

void WeaponPickup::setSpawnTile(sf::Vector2i tile)
{
	spawnTile = tile;
}

void WeaponPickup::despawn()
{
	active = false;

	Event::Data e;
	e.type = Event::DESPAWN_WEAPON;
	e.pickupType = type;
	e.tile = spawnTile;
	EventManager::triggerEvent(e);
}
