//==========================//
// Snake.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Enemy.h"

class Snake : public Enemy
{
public:
	// Constructor
	Snake(int type);
	// Destructor
	virtual ~Snake();

	// Methods
	void init();
	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	void shoot();

protected:
	float shootTimer;
	float nextShootTime;

	// Helpers
	float getNextShootTime(float low, float high);
};

#endif