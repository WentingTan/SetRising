//==========================//
// EnemyManager.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "EnemyManager.h"
#include "EventManager.h"
#include "Laser.h"
#include "FreezeRay.h"
#include "Flame.h"
#include "Player.h"
#include "Blackhole.h"

#include <fstream>

//==============================================================================
// EMScrollHandler::handleEvent(Event::Data)
// Handles Event::SCROLL by calling EnemyManager::scroll() through its internal
// EnemyManager pointer.
//==============================================================================
void EMScrollHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::SCROLL)
		pEM->scroll(sf::Vector2f(e.scrollX, e.scrollY));
}


void EMSpawnHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::SPAWN_ENEMY)
		pEM->spawn(sf::Vector2f(e.posX, e.posY), e.tile, e.enemyType);
}

// Also acts as the handler to despawn enemies on a game over
void EMTransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION || e.type == Event::PLAYER_DEATH_ANIM_DONE)
		pEM->clear();
}

void EMNewMapHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::NEW_MAP)
		pEM->setTileMap((TileMap*)e.map);
}

void EMPlayerMovedHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_MOVED)
		pEM->setPlayerPosition(sf::Vector2f(e.posX, e.posY));
}

// Constructor
EnemyManager::EnemyManager()
{
	pSnakes = NULL;
	sSnakes = NULL;
	wBats = NULL;
	dBats = NULL;
	crawlers = NULL;
	scrollHandler = NULL;
	spawnHandler = NULL;
	transitionHandler = NULL;
	newMapHandler = NULL;
}
	// Destructor
EnemyManager::~EnemyManager()
{
	if (pSnakes)
		delete [] pSnakes;
	if (sSnakes)
		delete [] sSnakes;
	if (wBats)
		delete [] wBats;
	if (dBats)
		delete [] dBats;
	if (crawlers)
		delete []crawlers;
	if (scrollHandler)
		delete scrollHandler;
	if (spawnHandler)
		delete spawnHandler;
	if (transitionHandler)
		delete transitionHandler;
	if (newMapHandler)
		delete newMapHandler;
	if (pMovedHandler)
		delete pMovedHandler;
}

void EnemyManager::init(sf::Texture *et, sf::Texture *bt, sf::Texture *ct)
{
	pSnakes = new PatrollingSnake[MAX_PATROLLING_SNAKES];
	sSnakes = new StationarySnake[MAX_STATIONARY_SNAKES];
	wBats = new WaitBat[MAX_WAIT_BATS];
	dBats = new DiveBat[MAX_DIVE_BATS];
	crawlers = new Crawler[MAX_CRAWLERS];

	for (int i = 0; i < MAX_PATROLLING_SNAKES; i++)
	{
		pSnakes[i].setTexture(et);
		pSnakes[i].init();
	}
	psInd = 0;

	for (int i = 0; i < MAX_STATIONARY_SNAKES; i++)
	{
		sSnakes[i].setTexture(et);
		sSnakes[i].init();
	}
	ssInd = 0;

	for (int i = 0; i < MAX_WAIT_BATS; i++)
	{
		wBats[i].setTexture(bt);
		wBats[i].init();
	}
	wbInd = 0;

	for (int i = 0; i < MAX_DIVE_BATS; i++)
	{
		dBats[i].setTexture(bt);
		dBats[i].init();
	}
	dbInd = 0;

	for (int i = 0; i < MAX_CRAWLERS; i++)
	{
		crawlers[i].setTexture(ct);
		crawlers[i].init();
	}
	crInd = 0;

	scrollHandler = new EMScrollHandler(this);
	spawnHandler = new EMSpawnHandler(this);
	transitionHandler = new EMTransitionHandler(this);
	newMapHandler = new EMNewMapHandler(this);
	pMovedHandler = new EMPlayerMovedHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::SPAWN_ENEMY, spawnHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
	EventManager::addHandler(Event::PLAYER_DEATH_ANIM_DONE, transitionHandler);
	EventManager::addHandler(Event::NEW_MAP, newMapHandler);
	EventManager::addHandler(Event::PLAYER_MOVED, pMovedHandler);
}

void EnemyManager::setTileMap(TileMap *tm)
{
	map = tm;
}

void EnemyManager::spawn(sf::Vector2f pos, sf::Vector2i tile, int type)
{
	std::ofstream log("log.txt", std::ios::app);
	switch (type)
	{
	case E_PATROLLING_SNAKE:
		pSnakes[psInd].activate(pos, tile, playerPos);
		psInd++;
		break;
	case E_STATIONARY_SNAKE:
		sSnakes[ssInd].activate(pos, tile, playerPos);
		ssInd++;
		break;
	case E_WAIT_BAT:
		wBats[wbInd].activate(pos, tile, playerPos);
		wbInd++;
		break;
	case E_DIVE_BAT:
		dBats[dbInd].activate(pos, tile, playerPos);
		dbInd++;
		break;
	case E_CRAWLER:
		crawlers[crInd].activate(pos, tile, playerPos);
		crInd++;
		break;
	default:
		break;
	}
	log.close();
}

void EnemyManager::scroll(sf::Vector2f ds)
{
	// Scroll active patrolling snakes
	for (int i = 0; i < psInd; i++)
		pSnakes[i].scroll(ds);

	// Scroll active stationary snakes
	for (int i = 0; i < ssInd; i++)
		sSnakes[i].scroll(ds);

	// Scroll active wait bats
	for (int i = 0; i < wbInd; i++)
		wBats[i].scroll(ds);

	// Scroll active dive bats
	for (int i = 0; i < dbInd; i++)
		dBats[i].scroll(ds);

	// Scroll active crawlers
	for (int i = 0; i < crInd; i++)
		crawlers[i].scroll(ds);
}

bool EnemyManager::checkCollisions(Laser *laser)
{
	bool collided;

	// Check for collisions with active patrolling snakes
	for (int i = 0; i < psInd; i++)
	{
		if (pSnakes[i].checkCollision(laser, collided))
			remove(i, E_PATROLLING_SNAKE);
		if (collided)
			return true;
	}

	// Check for collisions with active stationary snakes
	for (int i = 0; i < ssInd; i++)
	{
		if (sSnakes[i].checkCollision(laser, collided))
			remove(i, E_STATIONARY_SNAKE);
		if (collided)
			return true;
	}

	// Check for collisions with active wait bats
	for (int i = 0; i < wbInd; i++)
	{
		if (wBats[i].checkCollision(laser, collided))
			remove(i, E_WAIT_BAT);
		if (collided)
			return true;
	}

	// Check for collisions with active dive bats
	for (int i = 0; i < dbInd; i++)
	{
		if (dBats[i].checkCollision(laser, collided))
			remove(i, E_DIVE_BAT);
		if (collided)
			return true;
	}

	// Check for collisions with active crawlers
	for (int i = 0; i < crInd; i++)
	{
		if (crawlers[i].checkCollision(laser, collided))
			remove(i, E_CRAWLER);
		if (collided)
			return true;
	}

    return false;
}

bool EnemyManager::checkCollisions(FreezeRay *fRay)
{
	bool collided;

	// Check for collisions with active patrolling snakes
	for (int i = 0; i < psInd; i++)
	{
		if (pSnakes[i].checkCollision(fRay, collided))
			remove(i, E_PATROLLING_SNAKE);
		if (collided)
			return true;
	}

	// Check for collisions with active stationary snakes
	for (int i = 0; i < ssInd; i++)
	{
		if (sSnakes[i].checkCollision(fRay, collided))
			remove(i, E_STATIONARY_SNAKE);
		if (collided)
			return true;
	}

	// Check for collisions with active wait bats
	for (int i = 0; i < wbInd; i++)
	{
		if (wBats[i].checkCollision(fRay, collided))
			remove(i, E_WAIT_BAT);
		if (collided)
			return true;
	}

	// Check for collisions with active dive bats
	for (int i = 0; i < dbInd; i++)
	{
		if (dBats[i].checkCollision(fRay, collided))
			remove(i, E_DIVE_BAT);
		if (collided)
			return true;
	}

	// Check for collisions with active crawlers
	for (int i = 0; i < crInd; i++)
	{
		if (crawlers[i].checkCollision(fRay, collided))
			remove(i, E_CRAWLER);
		if (collided)
			return true;
	}

    return false;
}

void EnemyManager::checkCollisions(Flame *flame)
{
	// Check for collisions with active patrolling snakes
	for (int i = 0; i < psInd; i++)
		pSnakes[i].checkCollision(flame);

	// Check for collisions with active stationary snakes
	for (int i = 0; i < ssInd; i++)
		sSnakes[i].checkCollision(flame);

	// Check for collisions with active wait bats
	for (int i = 0; i < wbInd; i++)
		wBats[i].checkCollision(flame);

	// Check for collisions with active dive bats
	for (int i = 0; i < dbInd; i++)
		dBats[i].checkCollision(flame);

	// Check for collisions with active crawlers
	for (int i = 0; i < crInd; i++)
		crawlers[i].checkCollision(flame);
}

void EnemyManager::checkCollisions(Blackhole *bh)
{
	// Check for collisions with active patrolling snakes
	for (int i = 0; i < psInd; i++)
		if (!pSnakes[i].isInGravField())
			pSnakes[i].checkCollisionBH(bh);

	// Check for collisions with active stationary snakes
	for (int i = 0; i < ssInd; i++)
		if (!sSnakes[i].isInGravField())
			sSnakes[i].checkCollisionBH(bh);

	// Check for collisions with active wait bats
	for (int i = 0; i < wbInd; i++)
		if (!wBats[i].isInGravField())
			wBats[i].checkCollisionBH(bh);

	// Check for collisions with active dive bats
	for (int i = 0; i < dbInd; i++)
		if (!dBats[i].isInGravField())
			dBats[i].checkCollisionBH(bh);

	// Check for collisions with active crawlers
	for (int i = 0; i < crInd; i++)
		if (!crawlers[i].isInGravField())
			crawlers[i].checkCollisionBH(bh);
}


//==============================================================================
// EnemyManager::checkFrozenCollisions(Player*, sf::FloatRect&)
// Checks for collisions between frozen enemies and the player.  If a collision
// is detected, the intersection FloatRect is filled in with the values of the
// intersecting ractanlge between the player and the enemy.
//==============================================================================
bool EnemyManager::checkFrozenCollisions(Player *p, sf::FloatRect& overlap)
{
	// Check for collisions with frozen patrolling snakes
	for (int i = 0; i < psInd; i++)
	{
		if (pSnakes[i].isFrozen())
		{
			if (pSnakes[i].checkCollision(p, overlap))
				return true;
		}
	}

	// Check for collisions with frozen stationary snakes
	for (int i = 0; i < ssInd; i++)
	{
		if (sSnakes[i].isFrozen())
		{
			if (sSnakes[i].checkCollision(p, overlap))
				return true;
		}
	}

	// Check for collisions with frozen wait bats
	for (int i = 0; i < wbInd; i++)
	{
		if (wBats[i].isFrozen())
		{
			if (wBats[i].checkCollision(p, overlap))
				return true;
		}
	}

	// Check for collisions with frozen dive bats
	for (int i = 0; i < dbInd; i++)
	{
		if (dBats[i].isFrozen())
		{
			if (dBats[i].checkCollision(p, overlap))
				return true;
		}
	}

	// Check for collisions with frozen crawlers
	for (int i = 0; i < crInd; i++)
	{
		if (crawlers[i].isFrozen())
		{
			if (crawlers[i].checkCollision(p, overlap))
				return true;
		}
	}

	return false;
}


//==============================================================================
// EnemyManager::checkCollisions(Player*)
// Checks for collisions between active enemies and the player.  If a collision
// is detected, a PLAYER_HIT event is generated.
//==============================================================================
void EnemyManager::checkCollisions(Player *player)
{
	sf::FloatRect overlap;

	// Check for collisions with patrolling snakes
	for (int i = 0; i < psInd; i++)
	{
		if (!pSnakes[i].isFrozen() && !pSnakes[i].isInGravField())
			if (pSnakes[i].checkCollision(player, overlap))
			{
				player->damage(SNAKE_DAMAGE);
				return;
			}
	}

	// Check for collisions with stationary snakes
	for (int i = 0; i < ssInd; i++)
	{
		if (!sSnakes[i].isFrozen() && !sSnakes[i].isInGravField())
			if (sSnakes[i].checkCollision(player, overlap))
			{
				player->damage(SNAKE_DAMAGE);
				return;
			}
	}

	// Check for collisions with wait bats
	for (int i = 0; i < wbInd; i++)
	{
		if (!wBats[i].isFrozen() && !wBats[i].isInGravField())
			if (wBats[i].checkCollision(player, overlap))
			{
				player->damage(BAT_DAMAGE);
				return;
			}
	}

	// Check for collisions with dive bats
	for (int i = 0; i < dbInd; i++)
	{
		if (!dBats[i].isFrozen() && !dBats[i].isInGravField())
			if (dBats[i].checkCollision(player, overlap))
			{
				player->damage(BAT_DAMAGE);
				return;
			}
	}

	// Check for collisions with crawlers
	for (int i = 0; i < crInd; i++)
	{
		if (!crawlers[i].isFrozen() && !crawlers[i].isInGravField())
			if (crawlers[i].checkCollision(player, overlap))
			{
				player->damage(CRAWLER_DAMAGE);
				return;
			}
	}
}

//===============================================
// EnemyManager::setPlayerPosition(sf::Vector2f)
// Stores the player's current position.
//===============================================
void EnemyManager::setPlayerPosition(sf::Vector2f pPos)
{
	playerPos = pPos;
}

void EnemyManager::update(float dt)
{
	Event::Data e;
	e.type = Event::ENEMY_DEATH;

	// Update active patrolling snakes
	int i = 0;
	while (pSnakes[i].isActive() && i < MAX_PATROLLING_SNAKES)
		if (pSnakes[i].update(dt, map))
			remove(i, E_PATROLLING_SNAKE);
		else
			i++;

	// Update active stationary snakes
	i = 0;
	while (sSnakes[i].isActive() && i < MAX_STATIONARY_SNAKES)
		if (sSnakes[i].update(dt, playerPos))
			remove(i, E_STATIONARY_SNAKE);
		else
			i++;

	// Update active wait bats
	i = 0;
	while (wBats[i].isActive() && i < MAX_WAIT_BATS)
		if (wBats[i].update(dt, playerPos))
			remove(i, E_WAIT_BAT);
		else
			i++;

	// Update active dive bats
	i = 0;
	while (dBats[i].isActive() && i < MAX_DIVE_BATS)
		if (dBats[i].update(dt, playerPos))
			remove(i, E_DIVE_BAT);
		else
			i++;

	// Update active crawlers
	i = 0;
	while (crawlers[i].isActive() && i < MAX_CRAWLERS)
		if (crawlers[i].update(dt, map))
			remove(i, E_CRAWLER);
		else
			i++;
}

void EnemyManager::draw(sf::RenderWindow& window)
{
	// Draw active patrolling snakes to the screen
	for (int i = 0; i < psInd; i++)
		pSnakes[i].draw(window);

	// Draw active stationary snakes to the screen
	for (int i = 0; i < ssInd; i++)
		sSnakes[i].draw(window);

	// Draw active wait bats to the screen
	for (int i = 0; i < wbInd; i++)
		wBats[i].draw(window);

	// Draw active dive bats to the screen
	for (int i = 0; i < dbInd; i++)
		dBats[i].draw(window);

	// Draw active crawlers to the screen
	for (int i = 0; i < crInd; i++)
		crawlers[i].draw(window);
}

//===========================================
// EnemyManager::clear()
// Deactivates all currently active enemies.
//===========================================
void EnemyManager::clear()
{
	// De-spawn active patrolling snakes
	for (int i = 0; i < psInd; i++)
		pSnakes[i].despawn();
	psInd = 0;

	// De-spawn active stationary snakes
	for (int i = 0; i < ssInd; i++)
		sSnakes[i].despawn();
	ssInd = 0;

	// De-spawn active wait bats
	for (int i = 0; i < wbInd; i++)
		wBats[i].despawn();
	wbInd = 0;

	// De-spawn active dive bats
	for (int i = 0; i < dbInd; i++)
		dBats[i].despawn();
	dbInd = 0;

	// De-spawn active crawlers
	for (int i = 0; i < crInd; i++)
		crawlers[i].despawn();
	crInd = 0;
}


void EnemyManager::remove(int ind, int type)
{
   int j;

	switch (type)
	{
	case E_PATROLLING_SNAKE:
		j = MAX_PATROLLING_SNAKES - 1;
		while (j > ind && !pSnakes[j].isActive())
			j--;
		pSnakes[ind].copy(pSnakes[j]);
		pSnakes[j].deactivate();
		psInd--;
		break;
	case E_STATIONARY_SNAKE:
		j = MAX_STATIONARY_SNAKES - 1;
		while (j > ind && !sSnakes[j].isActive())
			j--;
		sSnakes[ind].copy(sSnakes[j]);
		sSnakes[j].deactivate();
		ssInd--;
		break;
	case E_WAIT_BAT:
		j = MAX_WAIT_BATS - 1;
		while (j > ind && !wBats[j].isActive())
			j--;
		wBats[ind].copy(wBats[j]);
		wBats[j].deactivate();
		wbInd--;
		break;
	case E_DIVE_BAT:
		j = MAX_DIVE_BATS - 1;
		while (j > ind && !dBats[j].isActive())
			j--;
		dBats[ind].copy(dBats[j]);
		dBats[j].deactivate();
		dbInd--;
		break;
	case E_CRAWLER:
		j = MAX_CRAWLERS - 1;
		while (j > ind && !crawlers[j].isActive())
			j--;
		crawlers[ind].copy(crawlers[j]);
		crawlers[j].deactivate();
		crInd--;
		break;
	default:
		break;
	}
}