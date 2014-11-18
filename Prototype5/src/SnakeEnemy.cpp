//==========================//
// SnakeEnemy.cpp           //
// Author: Matthew Stephens //
//==========================//
#include "SnakeEnemy.h"

#include <fstream>
#include "AlphaOscillator.h"
#include "Event.h"
#include "EventManager.h"
#include "Constants.h"
#include "TileMap.h"


SnakeEnemy::SnakeEnemy():
	Entity()
{
	// Do nothing
}

SnakeEnemy::~SnakeEnemy()
{
	if (freezeBlinker)
		delete freezeBlinker;
}

void SnakeEnemy::init()
{
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);

	// Main hitbox dimensions
	hitbox.width = 94.0f;
	hitbox.height = 94.0f;

	// Frozen hitbox dimensions
	frozenBody.width = 62.0f;
	frozenBody.height = 94.0f;
	frozenTail.width = 20.0f;
	frozenTail.height = 72.0f;

	freezeBlinker = new AlphaOscillator(255, 0, 0.125f);
}

sf::Vector2i SnakeEnemy::getSpawnTile()
{
	return spawnTile;
}

void SnakeEnemy::deactivate()
{
	active = false;
}

void SnakeEnemy::freeze()
{
	frozen = true;
	sprite.setColor(sf::Color::Blue);

	sf::Vector2f pos = sprite.getPosition();

	// The frozen body hitbox is the same regardless of the frame
	frozenBody.top = pos.y - 0.5f * 94.0f;
	frozenBody.left = pos.x + ((dir == 1.0f ? -frozenBody.width : 0.0f) + dir * 47.0f);

	// The frozen tail hitbox coordinates depend on the frame at which the enemy was frozen
	switch (frame)
	{
	case 0:
		frozenTail.top = pos.y - 19.0f;
		frozenTail.left = pos.x + ((dir == 1.0f ? -frozenTail.width : 0.0f) + dir * -25.0f);
		break;
	// Frames 1 and 3 are the same
	case 1:
	case 3:
		frozenTail.top = pos.y - 25.0f;
		frozenTail.left = pos.x + ((dir == 1.0f ? -frozenTail.width : 0.0f) + dir * -34.0f);
		break;
	case 2:
		frozenTail.top = pos.y - 25.0f;
		frozenTail.left = pos.x + ((dir == 1.0f ? -frozenTail.width : 0.0f) + dir * -43.0f);
		break;
	default:
		break;
	}
}

//====================================================
// SnakeEnemy::isFrozen()
// Indicates whether or not the SnakeEnemy is frozen.
//====================================================
bool SnakeEnemy::isFrozen() const
{
	return frozen;
}

sf::FloatRect SnakeEnemy::getFrozenBodyHB() const
{
	return frozenBody;
}

sf::FloatRect SnakeEnemy::getFrozenTailHB() const
{
	return frozenTail;
}

//=================================
// Enemy::updateFreeze(float)
//=================================
void SnakeEnemy::updateFreeze(float dt)
{
	freezeTimer += dt;
		
	if (freezeTimer > 3.5f)
	{
		frozen = false;
		freezeTimer = 0.0f;
		sprite.setColor(sf::Color::White);
	}
	else if (freezeTimer > 2.75f)
	{
		freezeBlinker->update(dt);
		sprite.setColor(sf::Color(freezeBlinker->getAlpha(), freezeBlinker->getAlpha(), 255));
	}
}

//==================================
// SnakeEnemy::animate(float)
// Animates the Snake Enemy sprite.
//==================================
void SnakeEnemy::animate(float dt)
{
	animTimer += dt;

	sf::IntRect rect = sf::IntRect(0, 0, 128, 128);

	if (animTimer > SNAKE_FRAME_TIME)
	{
		frame = (frame + 1) % SNAKE_FRAMES;
		rect.left = frame * 128;
		sprite.setTextureRect(rect);
		animTimer = 0.0f;
	}
}

//===============================================================
// SnakeEnemy::shoot()
// Shoots an acid projectile by generating an ENEMY_SHOOT event.
//===============================================================
void SnakeEnemy::shoot()
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


bool SnakeEnemy::damage(int amount)
{
	health -= amount;
	if (health <= 0)
		return true;
	else
		return false;
}
void SnakeEnemy::commonActivate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	// Select a random frame to start the animation
	frame = (int)(((float)rand() / RAND_MAX) * 3.0f);
	animTimer = 0.0f;
	shootTimer = 0.0f;
	frozen = false;
	freezeTimer = 0.0f;
	sprite.setColor(sf::Color::White);

	// Determine the direction the enemy should face
	dir = pos.x - playerPos.x > 0.0f ? D_LEFT : D_RIGHT;

	sf::IntRect rect = sf::IntRect(0, 0, 128, 128);
	sprite.setTextureRect(rect);

	sf::FloatRect bounds = sprite.getGlobalBounds();
	pos.y -= 0.5f * 94.0f;
	sprite.setPosition(pos);
	spawnTile = tile;
	health = SNAKE_HEALTH;
	active = true;

	bounds = sprite.getGlobalBounds();
	hitbox.left = pos.x - 0.5f * 94.0f;
	hitbox.top = pos.y - 0.5f * 94.0f;

	bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	sprite.setScale(dir, 1.0f);
}

/*
void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(sprite);

	sf::RectangleShape hb;
	hb.setFillColor(sf::Color(0, 0, 0, 175));
	//hb.setPosition(hitbox.left, hitbox.top);
	//hb.setSize(sf::Vector2f(hitbox.width, hitbox.height));

	if (frozen)
	{
		hb.setPosition(frozenBody.left, frozenBody.top);
		hb.setSize(sf::Vector2f(frozenBody.width, frozenBody.height));
		window.draw(hb);

		hb.setPosition(frozenTail.left, frozenTail.top);
		hb.setSize(sf::Vector2f(frozenTail.width, frozenTail.height));
		window.draw(hb);
	}
}
*/


void SnakeEnemy::scroll(sf::Vector2f ds)
{
	sprite.move(-1.0f * ds);

	hitbox.left -= ds.x;
	hitbox.top -= ds.y;

	if (frozen)
	{
		frozenBody.left -= ds.x;
		frozenBody.top -= ds.y;
		frozenTail.left -= ds.x;
		frozenTail.top -= ds.y;
	}
}

//===================================================================================
// SnakeEnemy::getNextShootTime()
// Returns a random number between a high value and a low value, which will serve as
// the delay before the Snake Enemy shoots another projectile.
//===================================================================================
float SnakeEnemy::getNextShootTime(float low, float high)
{
	float r = (float)rand() / RAND_MAX;
	return low + r * (high - low);
}