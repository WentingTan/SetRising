//==========================//
// AcidSpit.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _BOSS_SPIT_H_
#define _BOSS_SPIT_H_

#include <SFML/Graphics.hpp>
#include "Entity.h"

class BossSpit : public Entity
{
public:
	// Constructor
	BossSpit();
	// Destructor
	~BossSpit();

	// Accessors
	int getDamage() const;
	float getDir() const;
	float getSpeed() const;

	// Methods
	void init();
	void activate(sf::Vector2f pos, float dir);
	void deactivate();
	void update(float dt);
	void copy(BossSpit& as);

private:
	int damage;
	float speed;
	float dir;
};

#endif