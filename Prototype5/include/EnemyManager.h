//==========================//
// Enemy.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include <SFML/Graphics.hpp>
#include "PatrollingSnake.h"
#include "StationarySnake.h"
#include "EventHandler.h"

// Forward Declarations
class Laser;
class FreezeRay;
class Player;
class EnemyManager;
class TileMap;

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

//==================================================
// EnemyManager EventHandler for Event::ENEMY_DEATH
//==================================================
class EMEDeathHandler : public EventHandler
{
public:
	// Constructor
	explicit EMEDeathHandler(EnemyManager *em): pEM(em) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	EnemyManager *pEM;
};

//====================================================
// EnemyManager EventHandler for Event::TM_TRANSITION
//====================================================
class EMTransitionHandler : public EventHandler
{
public:
	// Constructor
	explicit EMTransitionHandler(EnemyManager *em): pEM(em) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	EnemyManager *pEM;
};

//==============================================
// EnemyManager EventHandler for Event::NEW_MAP
//==============================================
class EMNewMapHandler : public EventHandler
{
public:
	// Constructor
	explicit EMNewMapHandler(EnemyManager *em): pEM(em) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	EnemyManager *pEM;
};

//===================================================
// EnemyManager EventHandler for Event::PLAYER_MOVED
//===================================================
class EMPlayerMovedHandler : public EventHandler
{
public:
	// Constructor
	explicit EMPlayerMovedHandler(EnemyManager *em): pEM(em) {}
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

	void init(sf::Texture *et, sf::Texture *dt);
	void setTileMap(TileMap *tm);

	bool checkFrozenCollisions(Player *p, sf::FloatRect& intersection);


	void setPlayerPosition(sf::Vector2f pPos);

	bool checkCollisions(Laser *laser);
	bool checkCollisions(FreezeRay *fRay);
	void checkCollisions(Player *player);

	void clear();
	void scroll(sf::Vector2f ds);
	void startDeathAnim(float x, float y);
	void spawn(sf::Vector2f pos, sf::Vector2i tile, int type);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	PatrollingSnake *pSnakes;
	StationarySnake *sSnakes;
	sf::Sprite death;
	bool deathAnim;
	float timer;
	int frame;
	int psInd;
	int ssInd;
	TileMap *map;

	sf::Vector2f playerPos;

	EventHandler *scrollHandler;
	EventHandler *spawnHandler;
	EventHandler *deathHandler;
	EventHandler *transitionHandler;
	EventHandler *newMapHandler;
	EventHandler *pMovedHandler;


	// Helper
	void remove(int ind, int type);
};

#endif