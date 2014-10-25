//==========================//
// EnemyManager.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "EnemyManager.h"

// Constructor
EnemyManager::EnemyManager()
{

}
	// Destructor
EnemyManager::~EnemyManager()
{

}

void EnemyManager::init()
{
	enemies = new Enemy[10];
	for (int i = 0; i < 10; i++)
		enemies[i].init();
	index = 0;
}
	
void EnemyManager::spawn(sf::Vector2f pos)
{
	enemies[index].activate(pos);
	index++;
}

void EnemyManager::scroll(sf::Vector2f ds)
{
	int i = 0;
	while (enemies[i].isActive())
		enemies[i++].scroll(ds);
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