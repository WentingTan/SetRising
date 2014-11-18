//==========================//
// PatrollingSnake.h        //
// Author: Matthew Stephens //
//==========================//
#ifndef _PATROLLING_SNAKE_H_
#define _PATROLLING_SNAKE_H_

#include "SnakeEnemy.h"

// Forward declarations
class TileMap;

class PatrollingSnake : public SnakeEnemy
{
public:
	// Constructor
	PatrollingSnake();
	// Destructor
	~PatrollingSnake();

	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	void update(float dt, TileMap *map);
    void copy(PatrollingSnake& e);
	void move(float x);

protected:
	float maxPatrolDist;
	float patrolDist;

	// Helpers
	void updatePatrol(float dt, TileMap *map);
	bool checkFloorEdge(TileMap *map);
};

#endif