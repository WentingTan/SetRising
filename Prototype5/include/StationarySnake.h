//==========================//
// StationarySnake.h        //
// Author: Matthew Stephens //
//==========================//
#ifndef _STATIONARY_SNAKE_H_
#define _STATIONARY_SNAKE_H_

#include "SnakeEnemy.h"

class StationarySnake : public SnakeEnemy
{
public:
	// Constructor
	StationarySnake();
	// Destructor
	~StationarySnake();

	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	void update(float dt, sf::Vector2f pPos);
    void copy(StationarySnake& e);

protected:
	int shots;
};

#endif