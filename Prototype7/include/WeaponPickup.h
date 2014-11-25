//==========================//
// WeaponPickup.h           //
// Author: Matthew Stephens //
//==========================//
#ifndef _WEAPON_PICKUP_H_
#define _WEAPON_PICKUP_H_

#include "Pickup.h"

class WeaponPickup : public Pickup
{
public:
	// Constructor
	WeaponPickup();
	// Destructor
	virtual ~WeaponPickup();

	// Methods
	void setSpawnTile(sf::Vector2i tile);
	void despawn();

protected:
	sf::Vector2i spawnTile;
};

#endif