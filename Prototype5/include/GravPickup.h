//==========================//
// GravPickup.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _GRAV_PICKUP_H_
#define _GRAV_PICKUP_H_

#include "Pickup.h"

class GravPickup : public Pickup
{
public:
	// Constructor
	GravPickup();
	// Destructor
	~GravPickup();

	// Methods
	void activate(sf::Vector2f pos);

    void copy(GravPickup& hp);

private:

};

#endif