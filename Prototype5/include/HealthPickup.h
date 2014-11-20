//==========================//
// HealthPickup.h           //
// Author: Matthew Stephens //
//==========================//
#ifndef _HEALTH_PICKUP_H_
#define _HEALTH_PICKUP_H_

#include "Pickup.h"

class HealthPickup : public Pickup
{
public:
	// Constructor
	HealthPickup();
	// Destructor
	~HealthPickup();
	
	// Accessors
	float getHealth() const;

	// Methods
	void activate(sf::Vector2f pos, int type);
    void copy(HealthPickup& hp);

private:
	float health;
};

#endif