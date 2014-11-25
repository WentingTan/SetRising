//==========================//
// AcidSpit.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _ACID_SPIT_H_
#define _ACID_SPIT_H_

#include <SFML/Graphics.hpp>
#include "Entity.h"

class AcidSpit : public Entity
{
public:
	// Constructor
	AcidSpit();
	// Destructor
	~AcidSpit();

	// Accessors
	int getDamage() const;
	float getDir() const;
    float getSpeed() const;

	// Methods
	void init();
	void activate(sf::Vector2f pos, float dir);
    void deactivate();
	void update(float dt);
    void copy(AcidSpit& as);

private:
	int damage;
	float speed;
	float dir;
};

#endif