//==========================//
// EnemyManager.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "EnemyManager.h"
#include "EventManager.h"
#include "Laser.h"

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
		pEM->spawn(sf::Vector2f(e.posX, e.posY), e.tile, e.dir);
}





// Constructor
EnemyManager::EnemyManager()
{

}
	// Destructor
EnemyManager::~EnemyManager()
{

}

void EnemyManager::init(sf::Texture *t)
{
	enemies = new Enemy[10];
	for (int i = 0; i < 10; i++)
	{
		enemies[i].setTexture(t);
		enemies[i].init();
	}
	index = 0;

	scrollHandler = new EMScrollHandler(this);
	spawnHandler = new EMSpawnHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::SPAWN_ENEMY, spawnHandler);
}
	
void EnemyManager::spawn(sf::Vector2f pos, sf::Vector2i tile, float dir)
{
	enemies[index].activate(pos, tile, dir);
	index++;
}

void EnemyManager::scroll(sf::Vector2f ds)
{
	int i = 0;
	while (enemies[i].isActive())
		enemies[i++].scroll(ds);
}

bool EnemyManager::checkCollisions(Laser *laser)
{
	int i = 0;
	while (enemies[i].isActive())
	{
		if (enemies[i].collidesWith((Entity*)laser))
		{
			// Enemy::damage() returns true if enemy is killed
			if (enemies[i].damage(laser->getDamage()))
			{
				Event::Data e;
				e.type = Event::ENEMY_DEATH;
				e.tile = enemies[i].getSpawnTile();
				EventManager::triggerEvent(e);

				remove(i);

			}
            return true;
		}
		i++;
	}
    return false;
}

void EnemyManager::update(float dt)
{

}

void EnemyManager::draw(sf::RenderWindow& window)
{
	int i = 0;
	while (enemies[i].isActive())
		enemies[i++].draw(window);
}

void EnemyManager::remove(int ind)
{
    enemies[ind].deactivate();
    int j = 0;
    int k = 9;

    // Maintain "sorted" order, i.e. all active lasers are before inactive ones
    while (j < k)
	{
        while (enemies[j].isActive() && j < 9)
            j++;
        while (!enemies[k].isActive() && k > 0)
            k--;
        if (j < k)
		{
            enemies[j].copy(enemies[k]);
            enemies[k].deactivate();
		}
	}
    index--;
}