//==========================//
// Laser.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _LASER_H_
#define _LASER_H_

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Laser : public Entity
{
public:
	// Constructor
	Laser();
	// Destructor
	~Laser();

	// Accessors
	int getDamage() const;
	float getDir() const;
    float getSpeed() const;

	// Methods
	void init();
	void activate(sf::Vector2f pos, float dir);
    void deactivate();
	void update(float dt);
    void copy(Laser& l);

private:
	int damage;
	float speed;
	float dir;
};

#endif