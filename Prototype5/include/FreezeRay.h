//==========================//
// FreezeRay.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _FREEZE_RAY_H
#define _FREEZE_RAY_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class FreezeRay : public Entity
{
public:
	// Constructor
	FreezeRay();
	// Destructor
	~FreezeRay();

	// Accessors
	int getDamage() const;
	float getDir() const;
    float getSpeed() const;

	// Methods
	void init();
	void activate(sf::Vector2f pos, float dir);
    void deactivate();
	bool update(float dt);
    void copy(FreezeRay& f);

private:
	int damage;
	float speed;
	float dir;
	float distance;
};

#endif