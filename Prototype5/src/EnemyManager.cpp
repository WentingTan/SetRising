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


void EMEDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_DEATH)
		pEM->startDeathAnim(e.posX, e.posY);
}

void EMTransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION)
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

}
	// Destructor
EnemyManager::~EnemyManager()
{
	if (pSnakes)
		delete [] pSnakes;
	if (sSnakes)
		delete [] sSnakes;
	if (scrollHandler)
		delete scrollHandler;
	if (spawnHandler)
		delete spawnHandler;
	if (deathHandler)
		delete deathHandler;
	if (transitionHandler)
		delete transitionHandler;
	if (newMapHandler)
		delete newMapHandler;
	if (pMovedHandler)
		delete pMovedHandler;
}


void EnemyManager::startDeathAnim(float x, float y)
{
	deathAnim = true;
	timer = 0.0f;
	frame = 0;
	death.setPosition(x, y);
	death.setTextureRect(sf::IntRect(0,0,128,128));
}

void EnemyManager::init(sf::Texture *et, sf::Texture *dt)
{
	pSnakes = new PatrollingSnake[MAX_PATROLLING_SNAKES];
	sSnakes = new StationarySnake[MAX_STATIONARY_SNAKES];
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

	death.setTexture(*dt);
	deathAnim = false;
	death.setTextureRect(sf::IntRect(0,0,128,128));
	death.setOrigin(64.0f, 64.0f);

	scrollHandler = new EMScrollHandler(this);
	spawnHandler = new EMSpawnHandler(this);
	deathHandler = new EMEDeathHandler(this);
	transitionHandler = new EMTransitionHandler(this);
	newMapHandler = new EMNewMapHandler(this);
	pMovedHandler = new EMPlayerMovedHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::SPAWN_ENEMY, spawnHandler);
	EventManager::addHandler(Event::ENEMY_DEATH, deathHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
	EventManager::addHandler(Event::NEW_MAP, newMapHandler);
	EventManager::addHandler(Event::PLAYER_MOVED, pMovedHandler);
}

void EnemyManager::setTileMap(TileMap *tm)
{
	map = tm;
}

void EnemyManager::spawn(sf::Vector2f pos, sf::Vector2i tile, int type)
{
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
	default:
		break;
	}
}

void EnemyManager::scroll(sf::Vector2f ds)
{
	// Scroll active patrolling snakes
	for (int i = 0; i < psInd; i++)
		pSnakes[i].scroll(ds);

	// Scroll active stationary snakes
	for (int i = 0; i < ssInd; i++)
		sSnakes[i].scroll(ds);

	if (deathAnim)
		death.move(-1.0f * ds);
}

bool EnemyManager::checkCollisions(Laser *laser)
{
	Event::Data e;
	e.type = Event::ENEMY_DEATH;

	// Check for collisions with active patrolling snakes
	for (int i = 0; i < psInd; i++)
	{
		if (pSnakes[i].collidesWith((Entity*)laser))
		{
			// Enemy::damage() returns true if enemy is killed
			if (pSnakes[i].damage(laser->getDamage()))
			{
				e.enemyType = E_PATROLLING_SNAKE;
				e.tile = pSnakes[i].getSpawnTile();
				e.posX = pSnakes[i].getPosition().x;
				e.posY = pSnakes[i].getPosition().y;
				EventManager::triggerEvent(e);

				remove(i, E_PATROLLING_SNAKE);
			}
            return true;
		}
	}

	// Check for collisions with active stationary snakes
	for (int i = 0; i < ssInd; i++)
	{
		if (sSnakes[i].collidesWith((Entity*)laser))
		{
			// Enemy::damage() returns true if enemy is killed
			if (sSnakes[i].damage(laser->getDamage()))
			{
				e.enemyType = E_STATIONARY_SNAKE;
				e.tile = sSnakes[i].getSpawnTile();
				e.posX = sSnakes[i].getPosition().x;
				e.posY = sSnakes[i].getPosition().y;
				EventManager::triggerEvent(e);

				remove(i, E_STATIONARY_SNAKE);
			}
            return true;
		}
	}

    return false;
}


bool EnemyManager::checkCollisions(FreezeRay *fRay)
{
	Event::Data e;
	e.type = Event::ENEMY_DEATH;

	// Check for collisions with active patrolling snakes
	for (int i = 0; i < psInd; i++)
	{
		if (pSnakes[i].collidesWith((Entity*)fRay))
		{
			// Enemy::damage() returns true if enemy is killed
			pSnakes[i].freeze();
			if (pSnakes[i].damage(fRay->getDamage()))
			{
				e.enemyType = E_PATROLLING_SNAKE;
				e.tile = pSnakes[i].getSpawnTile();
				e.posX = pSnakes[i].getPosition().x;
				e.posY = pSnakes[i].getPosition().y;
				EventManager::triggerEvent(e);

				remove(i, E_PATROLLING_SNAKE);
			}
            return true;
		}
	}

	// Check for collisions with active stationary snakes
	for (int i = 0; i < ssInd; i++)
	{
		if (sSnakes[i].collidesWith((Entity*)fRay))
		{
			// Enemy::damage() returns true if enemy is killed
			sSnakes[i].freeze();
			if (sSnakes[i].damage(fRay->getDamage()))
			{
				e.enemyType = E_STATIONARY_SNAKE;
				e.tile = sSnakes[i].getSpawnTile();
				e.posX = sSnakes[i].getPosition().x;
				e.posY = sSnakes[i].getPosition().y;
				EventManager::triggerEvent(e);

				remove(i, E_STATIONARY_SNAKE);
			}
            return true;
		}
	}

    return false;
}

bool EnemyManager::checkCollisions(Flame *flame)
{
	Event::Data e;
	e.type = Event::ENEMY_DEATH;

	// Check for collisions with active patrolling snakes
	for (int i = 0; i < psInd; i++)
		if (pSnakes[i].collidesWith((Entity*)flame))
		{
			if (pSnakes[i].flameDamage())
			{
				if (pSnakes[i].damage(flame->getDamage()))
				{
					e.enemyType = E_PATROLLING_SNAKE;
					e.tile = pSnakes[i].getSpawnTile();
					e.posX = pSnakes[i].getPosition().x;
					e.posY = pSnakes[i].getPosition().y;
					EventManager::triggerEvent(e);

					remove(i, E_PATROLLING_SNAKE);
				}
			}
            return true;
		}

	// Check for collisions with active stationary snakes
	for (int i = 0; i < ssInd; i++)
		if (sSnakes[i].collidesWith((Entity*)flame))
		{
			if (sSnakes[i].flameDamage())
			{
				if (sSnakes[i].damage(flame->getDamage()))
				{
					e.enemyType = E_STATIONARY_SNAKE;
					e.tile = sSnakes[i].getSpawnTile();
					e.posX = sSnakes[i].getPosition().x;
					e.posY = sSnakes[i].getPosition().y;
					EventManager::triggerEvent(e);

					remove(i, E_STATIONARY_SNAKE);
				}
			}
			return true;
		}

    return false;
}




//==============================================================================
// EnemyManager::checkFrozenCollisions(Player*, sf::FloatRect&)
// Checks for collisions between frozen enemies and the player.  If a collision
// is detected, the intersection FloatRect is filled in with the values of the
// intersecting ractanlge between the player and the enemy.
//==============================================================================
bool EnemyManager::checkFrozenCollisions(Player *p, sf::FloatRect& intersection)
{
	// Check for collisions with frozen patrolling snakes
	for (int i = 0; i < psInd; i++)
	{
		if (pSnakes[i].isFrozen())
		{
			if (pSnakes[i].getFrozenBodyHB().intersects(p->getHitBox(), intersection))
				return true;
			if (pSnakes[i].getFrozenTailHB().intersects(p->getHitBox(), intersection))
				return true;
		}
	}

	// Check for collisions with frozen stationary snakes
	for (int i = 0; i < ssInd; i++)
	{
		if (sSnakes[i].isFrozen())
		{
			if (sSnakes[i].getFrozenBodyHB().intersects(p->getHitBox(), intersection))
				return true;
			if (sSnakes[i].getFrozenTailHB().intersects(p->getHitBox(), intersection))
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
	Event::Data e;
	e.type = Event::PLAYER_HIT;

	// Check for collisions with patrolling snakes
	for (int i = 0; i < psInd; i++)
	{
		if (!pSnakes[i].isFrozen() && pSnakes[i].getHitbox().intersects(player->getHitBox()))
		{
			e.damage = SNAKE_DAMAGE;
			EventManager::triggerEvent(e);
			return;
		}
	}

	// Check for collisions with stationary snakes
	for (int i = 0; i < ssInd; i++)
	{
		if (!sSnakes[i].isFrozen() && sSnakes[i].getHitbox().intersects(player->getHitBox()))
		{
			e.damage = SNAKE_DAMAGE;
			EventManager::triggerEvent(e);
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
	// Update active patrolling snakes
	for (int i = 0; i < psInd; i++)
		pSnakes[i].update(dt, map);

	// Update active stationary snakes
	for (int i = 0; i < ssInd; i++)
		sSnakes[i].update(dt, playerPos);

	if (deathAnim)
	{
		timer += dt;

		if (timer > 0.125f)
		{
			timer = 0.0f;
			if (frame == 4)
				deathAnim = false;
			else
			{
				frame++;
				sf::IntRect rect(0,0,128,128);
				rect.left = frame * 128;
				death.setTextureRect(rect);
			}
		}
	}

}

void EnemyManager::draw(sf::RenderWindow& window)
{
	// Draw active patrolling snakes to the screen
	for (int i = 0; i < psInd; i++)
		pSnakes[i].draw(window);

	// Draw active stationary snakes to the screen
	for (int i = 0; i < ssInd; i++)
		sSnakes[i].draw(window);

	if (deathAnim)
		window.draw(death);
}

//===========================================
// EnemyManager::clear()
// Deactivates all currently active enemies.
//===========================================
void EnemyManager::clear()
{
	Event::Data e;
	e.type = Event::DESPAWN_ENEMY;

	// De-spawn active patrolling snakes
	e.enemyType = E_PATROLLING_SNAKE;
	for (int i = 0; i < psInd; i++)
	{
		pSnakes[i].deactivate();
		e.tile = pSnakes[i].getSpawnTile();
		EventManager::triggerEvent(e);
	}
	psInd = 0;

	// De-spawn active stationary snakes
	e.enemyType = E_STATIONARY_SNAKE;
	for (int i = 0; i < ssInd; i++)
	{
		sSnakes[i].deactivate();
		e.tile = sSnakes[i].getSpawnTile();
		EventManager::triggerEvent(e);
	}
	ssInd = 0;
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
	default:
		break;
	}
}