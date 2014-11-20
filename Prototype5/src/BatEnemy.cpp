//==========================//
// BatEnemy.cpp             //
// Author: Matthew Stephens //
//==========================//
#include "BatEnemy.h"

#include <fstream>
#include "AlphaOscillator.h"
#include "Event.h"
#include "EventManager.h"
#include "Constants.h"
#include "TileMap.h"


BatEnemy::BatEnemy():
	Entity()
{
	// Do nothing
}

BatEnemy::~BatEnemy()
{
	if (freezeBlinker)
		delete freezeBlinker;
}

void BatEnemy::init()
{
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, BAT_IMG_SIZE, BAT_IMG_SIZE));
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);

	freezeBlinker = new AlphaOscillator(255, 0, 0.125f);
}

sf::Vector2i BatEnemy::getSpawnTile()
{
	return spawnTile;
}

void BatEnemy::deactivate()
{
	active = false;
}

void BatEnemy::flameDamage()
{
	flameTimer = 0.0f;
	doFlameDamage = true;
	frozen = false;
	sprite.setColor(sf::Color::Red);
}

void BatEnemy::freeze()
{
	if (frozen)
		return;

	frozen = true;
	sprite.setColor(sf::Color::Blue);

	freezeTimer = 0.0f;
}

//====================================================
// BatEnemy::isFrozen()
// Indicates whether or not the BatEnemy is frozen.
//====================================================
bool BatEnemy::isFrozen() const
{
	return frozen;
}

//=================================
// Enemy::updateFreeze(float)
//=================================
void BatEnemy::updateFreeze(float dt)
{
	freezeTimer += dt;
		
	if (freezeTimer > FREEZE_TIME)
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

bool BatEnemy::updateFlame(float dt)
{
	float amount = flameTimer > 0.0f ? 0.3f * FLAME_DAMAGE * dt : FLAME_DAMAGE * dt;
	
	flameTimer += dt;

	if (flameTimer > FLAME_TIME)
	{
		doFlameDamage = false;
		sprite.setColor(sf::Color::White);
	}

	if (damage(amount))
		return true;
	else
		return false;
}

//==================================
// BatEnemy::animate(float)
// Animates the Bat Enemy sprite.
//==================================
void BatEnemy::animate(float dt)
{
	animTimer += dt;

	if (animTimer > BAT_FRAME_TIME)
	{
		frame = (frame + 1) % BAT_FRAMES;
		setFrame(frame);
		animTimer = 0.0f;
	}
}

void BatEnemy::setFrame(int frame)
{
	sf::IntRect rect = sf::IntRect(0, 0, BAT_IMG_SIZE, BAT_IMG_SIZE);
	rect.left = frame * BAT_IMG_SIZE;
	sprite.setTextureRect(rect);

	// Set the hitbox based on the current frame
	sf::Vector2f pos = sprite.getPosition();
	switch(frame)
	{
	case 0:
	case 8:
		hitbox.width = 38.0f;
		hitbox.height = 38.0f;
		hitbox.top = pos.y - 15.0f;
		hitbox.left = pos.x + ((dir == D_RIGHT ? -hitbox.width : 0.0f) + dir * 16.0f);
		break;
	case 1:
	case 7:
		hitbox.width = 46.0f;
		hitbox.height = 24.0f;
		hitbox.top = pos.y - 7.0f;
		hitbox.left = pos.x + ((dir == D_RIGHT ? -hitbox.width : 0.0f) + dir * 19.0f);
		break;
	case 2:
	case 6:
		hitbox.width = 44.0f;
		hitbox.height = 22.0f;
		hitbox.top = pos.y;
		hitbox.left = pos.x + ((dir == D_RIGHT ? -hitbox.width : 0.0f) + dir * 16.0f);
		break;
	case 3:
	case 5:
		hitbox.width = 22.0f;
		hitbox.height = 24.0f;
		hitbox.top = pos.y - 3.0f;
		hitbox.left = pos.x + ((dir == D_RIGHT ? -hitbox.width : 0.0f) + dir * 9.0f);
		break;
	case 4:
		hitbox.width = 16.0f;
		hitbox.height = 40.0f;
		hitbox.top = pos.y - 13.0f;
		hitbox.left = pos.x + ((dir == D_RIGHT ? -hitbox.width : 0.0f) + dir * 7.0f);
		break;
	case 9:
		hitbox.width = 22.0f;
		hitbox.height = 46.0f;
		hitbox.top = pos.y - 24.0f;
		hitbox.left = pos.x + ((dir == D_RIGHT ? -hitbox.width : 0.0f) + dir * 9.0f);
		break;
	default:
		break;
	}
}

bool BatEnemy::damage(float amount)
{
	health -= amount;
	if (health <= 0.0f)
		return true;
	else
		return false;
}
void BatEnemy::commonActivate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	animTimer = 0.0f;
	frozen = false;
	doFlameDamage = false;
	freezeTimer = 0.0f;
	flameTimer = 0.0f;
	sprite.setColor(sf::Color::White);

	// Determine the direction the enemy should face
	dir = pos.x - playerPos.x > 0.0f ? D_LEFT : D_RIGHT;

	// Select a random frame to start the animation
	frame = (int)(((float)rand() / RAND_MAX) * 3.0f);
	setFrame(frame);

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setPosition(pos);
	spawnTile = tile;
	health = BAT_HEALTH;
	active = true;

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
