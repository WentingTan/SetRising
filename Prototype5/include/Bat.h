//==========================//
// BatEnemy.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _BAT_H_
#define _BAT_H_

#include "Enemy.h"

// Forward declarations
class AlphaOscillator;
class TileMap;

class Bat : public Enemy
{
public:
	// Constructor
	Bat(int type);
	// Destructor
	virtual ~Bat();

	void init();
	//void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);

protected:
	
};

#endif