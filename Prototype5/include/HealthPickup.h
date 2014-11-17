//==========================//
// HealthPickup.h           //
// Author: Matthew Stephens //
//==========================//
#ifndef _HEALTH_PICKUP_H_
#define _HEALTH_PICKUP_H_

#include "Entity.h"

// Forward declaration
class AlphaOscillator;

namespace HPickup
{
	const int SMALL = 0;
	const int LARGE = 1;

	const int SM_HEALTH = 2;
	const int LG_HEALTH = 5;

	const float TIME_TILL_FADE = 3.5f;
	const float FADE_TIME = 1.5f;
	const float FD_HI_ALPHA = 255.0f;
	const float FD_LO_ALPHA = 100.0f;
	const float FD_CYCLE = 0.1f;
};

class HealthPickup : public Entity
{
public:
	// Constructor
	HealthPickup();
	// Destructor
	~HealthPickup();
	
	// Accessors
	int getHealth() const;

	// Methods
	void init();
	void activate(sf::Vector2f pos, int size, sf::Vector2i tile);
	bool update(float dt);
	void deactivate();

    void swap(HealthPickup& hp);

private:
	int health;
	float time;
	bool fade;
	sf::Vector2i tile;
	AlphaOscillator *fadeFlash;
};

#endif