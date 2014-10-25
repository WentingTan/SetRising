//==========================//
// Enemy.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include <SFML/Graphics.hpp>
#include "Enemy.h"

class EnemyManager
{
public:
	// Constructor
	EnemyManager();
	// Destructor
	~EnemyManager();

	void init();

	void scroll(sf::Vector2f ds);
	
	void spawn(sf::Vector2f pos);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	Enemy *enemies;
	int index;
};

#endif