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
	virtual ~Pickup();

	// Accessors
	int getType() const;
	float getSize() const;

	// Methods
	void init(int pType);
	void activate(sf::Vector2f pos, float size);
	void deactivate();
	bool update(float dt);
	void copy(Pickup& p);

protected:
	int type;
	float size;
	float time;
	AlphaOscillator fadeBlinker;

	static const sf::IntRect healthRect;
	static const sf::IntRect gBombRect;
	static const sf::IntRect freezeRect;
	static const sf::IntRect flameRect;
	static const sf::IntRect flamethrowerRect;
	static const sf::IntRect freezerayRect;
};

#endif