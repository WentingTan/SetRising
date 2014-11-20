//==========================//
// Snake.cpp                //
// Author: Matthew Stephens //
//==========================//
#include "Snake.h"
#include "Constants.h"
#include "EventManager.h"

Snake::Snake(int type):
	Enemy(type, SNAKE_HEALTH)
{
	// Do nothing
}

Snake::~Snake()
{
	// Do nothing
}

void Snake::init()
{
	Enemy::init(SNAKE_FILE);
}

void Snake::activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	commonActivate(pos, tile, playerPos);
	move(sf::Vector2f(0.0f, -0.5f * 94.0f));
}

//================================================================================
// Snake::shoot()
// The snake spits an acid projectile by generating an ENEMY_SHOOT event with the
// appropriate data.
//================================================================================
void Snake::shoot()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	Event::Data e;

	e.type = Event::ENEMY_SHOOT;
	e.weaponType = W_ACID_SPIT;
	if (dir > 0.0f)
		e.posX = bounds.left + 0.8f * bounds.width;
	else
		e.posX = bounds.left + 0.2f * bounds.width;
    e.posY = bounds.top + 0.5f * bounds.height;
	e.dir = dir;

	EventManager::triggerEvent(e);
}

//===================================================================================
// Snake::getNextShootTime()
// Returns a random number between a high value and a low value, which will serve as
// the delay before the Snake shoots another projectile.
//===================================================================================
float Snake::getNextShootTime(float low, float high)
{
	float r = (float)rand() / RAND_MAX;
	return low + r * (high - low);
}