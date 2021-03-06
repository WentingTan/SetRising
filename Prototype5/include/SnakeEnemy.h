//==========================//
// SnakeEnemy.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _SNAKE_ENEMY_H_
#define _SNAKE_ENEMY_H_

#include "Entity.h"

// Forward declarations
class AlphaOscillator;

class SnakeEnemy : public Entity
{
public:
	// Constructor
	SnakeEnemy();
	// Destructor
	virtual ~SnakeEnemy();

	void init();
	sf::Vector2i getSpawnTile();
	void deactivate();
	void freeze();
	bool isFrozen() const;
	void flameDamage();
	void checkGravField(sf::Vector2f pos, float d);
	bool isInGravField() const;
	sf::FloatRect getFrozenBodyHB() const;
	sf::FloatRect getFrozenTailHB() const;
	bool damage(float amount);
	void shoot();
	void scroll(sf::Vector2f ds);

protected:
	sf::Vector2i spawnTile;
	float health;
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
	bool doFlameDamage;
	float flameTimer;
	bool inGravField;
	float distToBH;
	sf::Vector2f dirToBH;
	float distMoved;

	// Helpers
	void animate(float dt);
	void updateFreeze(float dt);
	bool updateFlame(float dt);
	bool updateGravity(float dt);
	void commonActivate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	float getNextShootTime(float low, float high);
};

#endif