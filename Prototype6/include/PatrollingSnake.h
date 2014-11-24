//==========================//
// PatrollingSnake.h        //
// Author: Matthew Stephens //
//==========================//
#ifndef _PATROLLING_SNAKE_H_
#define _PATROLLING_SNAKE_H_

#include "Snake.h"

// Forward declarations
class TileMap;

class PatrollingSnake : public Snake
{
public:
	// Constructor
	PatrollingSnake();
	// Destructor
	virtual ~PatrollingSnake();

	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	bool update(float dt, TileMap *map);
    void copy(PatrollingSnake& e);

protected:
	float maxPatrolDist;
	float patrolDist;

	// Helpers
	void updatePatrol(float dt, TileMap *map);
	bool checkFloorEdge(TileMap *map);
};

#endif