//==========================//
// DiveBat.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "DiveBat.h"

#include "Event.h"
#include "EventManager.h"
#include "Constants.h"
#include <fstream>
#include <math.h>

DiveBat::DiveBat():
	Bat(E_DIVE_BAT)
{
	// Do nothing
}

DiveBat::~DiveBat()
{

}


bool DiveBat::update(float dt, sf::Vector2f pPos)
{
	if (inGravField)
	{
		animate(dt);
		return updateGravity(dt);
	}
	else if (frozen)
		updateFreeze(dt);
	else
	{
		animate(dt);

		if (dive)
			move(sf::Vector2f(diveDir.x * speed * dt, diveDir.y * speed * dt));
		else
		{
			move(sf::Vector2f(dir * speed * dt, 0.0f));

			sf::Vector2f dist = pPos - sprite.getPosition();
			if (dist.x < DB_TRIGGER_DIST && dist.x > -DB_TRIGGER_DIST)
			{
				// Normalize and set the dive direction
				float len = sqrt(dist.x * dist.x + dist.y *dist.y);
				diveDir.x = dist.x / len;
				diveDir.y = dist.y / len;
				dive = true;
			}
		}

		if (onFire)
			return updateFlame(dt);
	}
	return false;
}


void DiveBat::activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	// Do activation steps common to all types of enemies
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
	onFire = e.onFire;
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