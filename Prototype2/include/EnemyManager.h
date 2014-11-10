//==========================//
// Enemy.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Boss.h"
#include "TileMap.h"
#include "EventHandler.h"

// Forward Declarations
class Laser;
class EnemyManager;

//=============================================
// EnemyManager EventHandler for Event::SCROLL
//=============================================
class EMScrollHandler : public EventHandler
{
public:
	// Constructor
	explicit EMScrollHandler(EnemyManager *em): pEM(em) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	EnemyManager *pEM;
};

//==================================================
// EnemyManager EventHandler for Event::SPAWN_ENEMY
//==================================================
class EMSpawnHandler : public EventHandler
{
public:
	// Constructor
	explicit EMSpawnHandler(EnemyManager *em): pEM(em) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	EnemyManager *pEM;
};


class BossSpawnHandler : public EventHandler
{
public:
	// Constructor
	explicit BossSpawnHandler(EnemyManager *em) : pEM(em) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	EnemyManager *pEM;
};




class EnemyManager
{
public:
	// Constructor
	EnemyManager();
	// Destructor
	~EnemyManager();

	void init(sf::Texture *t, sf::Texture *b);
	void spawnBoss(sf::Vector2f pos, sf::Vector2i tile, float dir);
	void init(sf::Texture *t);

	bool checkCollisions(Laser *laser);

	void scroll(sf::Vector2f ds);
	
	void spawn(sf::Vector2f pos, sf::Vector2i tile, float dir);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	Enemy *enemies;
	int index;
	EventHandler *scrollHandler;
	EventHandler *spawnHandler;
	Boss *bosses;
	EventHandler *bSpawnHandler;
	// Helper
	void remove(int ind);
};

#endif