//==========================//
// BatEnemy.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _BAT_ENEMY_H_
#define _BAT_ENEMY_H_

#include "Entity.h"

// Forward declarations
class AlphaOscillator;
class TileMap;

class BatEnemy : public Entity
{
public:
	// Constructor
	BatEnemy();
	// Destructor
	virtual ~BatEnemy();

	void init();
	sf::Vector2i getSpawnTile();
	void deactivate();
	void freeze();
	bool isFrozen() const;
	void flameDamage();
	bool damage(float amount);

protected:
	sf::Vector2i spawnTile;
	float health;
	float dir;
	float animTimer;
	int frame;
	bool frozen;
	float freezeTimer;
	sf::FloatRect frozenBody;
	sf::FloatRect frozenTail;	
	AlphaOscillator *freezeBlinker;
	bool doFlameDamage;
	float flameTimer;

	// Helpers
	void setFrame(int frame);
	void animate(float dt);
	void updateFreeze(float dt);
	bool updateFlame(float dt);
	void commonActivate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
};

#endif