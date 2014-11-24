//==========================//
// IceBlock.cpp             //
// Author: Matthew Stephens //
//==========================//
#include "IceBlock.h"

#include <fstream>
#include "EventManager.h"
#include "Constants.h"
#include "Flame.h"
#include "FreezeRay.h"
#include "Laser.h"
#include "Player.h"


const float IceBlock::FADE_TIME = 0.4f;
const float IceBlock::ICE_HP = 0.5f * FLAME_DAMAGE;

IceBlock::IceBlock():
	Entity(),
	blinker(180.0f, 75.0f, 0.1f)
	
{
	// Do nothing
}

IceBlock::~IceBlock()
{

}

void IceBlock::deactivate()
{
	active = false;
}

void IceBlock::init()
{
	sprite.setTexture(*texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);

	active = false;
}

void IceBlock::activate(sf::Vector2f pos, sf::Vector2i tile)
{
	health = ICE_HP;
	health = ICE_HP;
	melted = melting = false;
	timer = 0.0f;
	blinker.reset();
	sprite.setColor(sf::Color(255, 255, 255, 180));

	sprite.setPosition(pos);
	spawnTile = tile;
	hitbox = sprite.getGlobalBounds();
	active = true;
}

bool IceBlock::checkCollision(Player *p, sf::FloatRect& overlap)
{
	sf::FloatRect hb = p->getHitBox();

	if (hitbox.intersects(hb, overlap))
		return true;
	return false;
}

bool IceBlock::checkCollision(Laser* l)
{
	if (melted)
		return false;

	sf::FloatRect hb = l->getHitbox();

	if (hitbox.intersects(hb))
		return true;
	else
		return false;
}

bool IceBlock::checkCollision(FreezeRay *fRay)
{
	if (melted)
		return false;

	sf::FloatRect hb = fRay->getHitbox();

	if (hitbox.intersects(hb))
		return true;
	else
		return false;
}

void IceBlock::checkCollision(Flame *f)
{
	if (melted)
		return;

	sf::FloatRect hb = f->getHitbox();

	if (hitbox.intersects(hb))
		melting = true;
	else
		melting = false;
}

bool IceBlock::update(float dt)
{
	if (melted)
	{
		timer += dt;

		if (timer > FADE_TIME)
			return true;
		else
		{
			blinker.update(dt);
			sprite.setColor(sf::Color(255, 255, 255, blinker.getAlpha()));
		}
	}
	if (melting)
		health -= FLAME_DAMAGE * dt;

	if (health <= 0.0f)
		melted = true;

	return false;
}

void IceBlock::despawn()
{
	active = false;
	melted = false;
	melting = false;
	timer = 0.0f;

	Event::Data e;
	e.type = Event::DESPAWN_BARRIER;
	e.enemyType = S_ICEBLOCK;
	e.tile = spawnTile;
	EventManager::triggerEvent(e);
}

void IceBlock::copy(IceBlock& ib)
{
	sprite.setPosition(ib.sprite.getPosition());
	sprite.setColor(ib.sprite.getColor());
	active = ib.active;
	melted = ib.melted;
	melting = ib.melting;
	timer = ib.timer;
	blinker = ib.blinker;
	health = ib.health;
	hitbox = ib.hitbox;
	spawnTile = ib.spawnTile;
}