//==========================//
// Enemy.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"



class Enemy : public Entity
{
public:
	// Constructor
	Enemy();
	// Destructor
	~Enemy();

	void init();
	void activate(sf::Vector2f pos, sf::Vector2i tile, float dir);
	sf::Vector2i getSpawnTile();
	void deactivate();
	bool damage(int amount);
	void update(float dt);
    void copy(Enemy& e);

private:
	sf::Vector2i spawnTile;
	int health;
	float timer;
	int frame;
};

#endif