//==========================//
// Crawler.h                //
// Author: Matthew Stephens //
//==========================//
#ifndef _CRAWLER_H_
#define _CRAWLER_H_

#include "Enemy.h"

// Forward dclarations
class TileMap;

class Crawler : public Enemy
{
public:
	// Constructor
	Crawler();
	// Destructor
	virtual ~Crawler();

	void init();
	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	bool update(float dt, TileMap *map);

	void copy(Crawler& c);

protected:
	float maxPatrolDist;
	float patrolDist;

	// Helpers
	void updatePatrol(float dt, TileMap *map);
	bool checkFloorEdge(TileMap *map);
};

#endif