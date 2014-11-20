//==========================//
// DiveBat.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "DiveBat.h"

#include "Event.h"
#include "EventManager.h"
#include "Constants.h"
#include <fstream>

DiveBat::DiveBat():
	BatEnemy()
{
	// Do nothing
}

DiveBat::~DiveBat()
{

}


bool DiveBat::update(float dt, sf::Vector2f pPos)
{
	if (frozen)
		updateFreeze(dt);
	else
	{
		animate(dt);

		if (dive)
			move(sf::Vector2f(diveDir.x * BAT_SPEED * dt, diveDir.y * BAT_SPEED * dt));
		else
		{
			move(sf::Vector2f(dir * BAT_SPEED * dt, 0.0f));

			sf::Vector2f dist = pPos - sprite.getPosition();
			if (dist.x < DB_TRIGGER_DIST && dist.x > -DB_TRIGGER_DIST)
			{
				// Normalize and set the dive direction
				diveDir = dist / sqrt(dist.x * dist.x + dist.y *dist.y);
				dive = true;
			}
		}

		if (doFlameDamage)
			return updateFlame(dt);
	}
	return false;
}


void DiveBat::activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	// Do activation steps common to both types of bat enemies
	commonActivate(pos, tile, playerPos);

	dive = false;
}

void DiveBat::copy(DiveBat& e)
{
    texture = e.texture;
	sprite = e.sprite;
	hitbox = e.hitbox;
	active = e.active;
    spawnTile = e.spawnTile;
	health = e.health;
	dir = e.dir;
	frame = e.frame;
	animTimer = e.animTimer;
	frozen = e.frozen;
	freezeTimer = e.freezeTimer;
	doFlameDamage = e.doFlameDamage;
	flameTimer = e.flameTimer;
	dive = e.dive;
	diveDir = e.diveDir;
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