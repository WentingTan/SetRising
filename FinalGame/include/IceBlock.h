//==========================//
// IceBlock.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _ICE_BLOCK_H_
#define _ICE_BLOCK_H_

#include "Entity.h"
#include "AlphaOscillator.h"

// Forward declarations
class Laser;
class FreezeRay;
class Flame;
class GravityBomb;
class Player;

class IceBlock : public Entity
{
public:
	// Constructor
	IceBlock();
	// Destructor
	virtual ~IceBlock();

	void init();
	void activate(sf::Vector2f pos, sf::Vector2i tile);
	bool update(float dt);
	void deactivate();
	void despawn();

	bool checkCollision(Laser *l);
	bool checkCollision(FreezeRay *fRay);
	void checkCollision(Flame *f);
	bool checkCollision(Player *p, sf::FloatRect& overlap);
	//bool checkCollision(GravityBomb *gb);

	void copy(IceBlock& ib);

protected:
	sf::Vector2i spawnTile;
	float health;
	float timer;
	bool melting;
	bool melted;
	AlphaOscillator blinker;

	static const float FADE_TIME;
	static const float ICE_HP;
};

#endif