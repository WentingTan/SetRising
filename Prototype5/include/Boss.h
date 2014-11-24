//==========================//
// StationarySnake.h        //
// Author: Matthew Stephens //
//==========================//
#ifndef _BOSS_H_
#define _BOSS_H_

#include "Snake.h"

class Boss : public Snake
{
public:
	// Constructor
	Boss();
	// Destructor
	virtual ~Boss();
	void init();

	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	bool update(float dt, sf::Vector2f pPos);
	void copy(Boss& e);

protected:
	int shots;
};

#endif