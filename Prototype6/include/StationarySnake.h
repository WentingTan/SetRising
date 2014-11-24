//==========================//
// StationarySnake.h        //
// Author: Matthew Stephens //
//==========================//
#ifndef _STATIONARY_SNAKE_H_
#define _STATIONARY_SNAKE_H_

#include "Snake.h"

class StationarySnake : public Snake
{
public:
	// Constructor
	StationarySnake();
	// Destructor
	virtual ~StationarySnake();

	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	bool update(float dt, sf::Vector2f pPos);
    void copy(StationarySnake& e);

protected:
	int shots;
};

#endif