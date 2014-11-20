//==========================//
// Flame.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _FLAME_H_
#define _FLAME_H_

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Flame : public Entity
{
public:
	// Constructor
	Flame();
	// Destructor
	~Flame();

	// Accessors
	int getDamage() const;

	// Methods
	void init();
	void activate(sf::Vector2f pos, float dir);
    void deactivate();
	void update(float dt);

private:
	int damage;
	int frame;
	float animTimer;

	bool setInactive;
};

#endif