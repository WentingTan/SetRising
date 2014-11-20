//==========================//
// Pickup.h                 //
// Author: Matthew Stephens //
//==========================//
#ifndef _PICKUP_H_
#define _PICKUP_H_

#include "Entity.h"
#include "AlphaOscillator.h"


class Pickup : public Entity
{
public:
	// Constructor
	Pickup();
	// Destructor
	~Pickup();

	// Methods
	void init();
	bool update(float dt);
	void deactivate();

protected:
	float time;
	AlphaOscillator fadeBlinker;
};

#endif