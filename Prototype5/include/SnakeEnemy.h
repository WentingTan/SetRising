//==========================//
// SnakeEnemy.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _SNAKE_ENEMY_H_
#define _SNAKE_ENEMY_H_

#include "Entity.h"

// Forward declarations
class AlphaOscillator;
class TileMap;

class SnakeEnemy : public Entity
{
public:
	// Constructor
	SnakeEnemy();
	// Destructor
	virtual ~SnakeEnemy();

	void init();
	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos, bool station);
	sf::Vector2i getSpawnTile();
	void deactivate();
	void freeze();
	bool isFrozen() const;
	bool isStationary();
	sf::FloatRect getFrozenBodyHB() const;
	sf::FloatRect getFrozenTailHB() const;
	bool damage(int amount);
	void shoot();
	void scroll(sf::Vector2f ds);

protected:
	sf::Vector2i spawnTile;
	int health;
	float dir;
	float animTimer;
	float shootTimer;
	int frame;
	bool frozen;
	float freezeTimer;
	sf::FloatRect frozenBody;
	sf::FloatRect frozenTail;	
	AlphaOscillator *freezeBlinker;
	float nextShootTime;

	// Helpers
	void animate(float dt);
	void updateFreeze(float dt);
	void commonActivate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	float getNextShootTime(float low, float high);
};

#endif