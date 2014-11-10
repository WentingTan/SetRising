//==========================//
// Enemy.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"

namespace EnemyNS
{
	enum state
	{
		S_STAND,
		S_SHOOT,
		S_PATROL
	};
	enum graphics
	{
		G_STAND = 0,
		G_WALK0 = 1,
		G_WALK1 = 2,
		G_WALK2 = 3,
		G_SHOOT = 4
	};
	// Images per row in Player texture
	const int IRP = 5;
	// Image size
	const sf::Vector2i IMG_SIZE = sf::Vector2i(64, 64);

	const float LEFT = -1.0f;
	const float RIGHT = 1.0f;
}

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
	void kill();

    void copy(Enemy& e);
	void setGraphics(EnemyNS::graphics g, float dir);


private:
	sf::Vector2i spawnTile;
	int health;
};

#endif