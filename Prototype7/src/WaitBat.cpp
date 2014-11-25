//==========================//
// WaitBat.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "WaitBat.h"

#include "Event.h"
#include "EventManager.h"
#include "Constants.h"


WaitBat::WaitBat():
	Bat(E_WAIT_BAT)
{
	// Do nothing
}

WaitBat::~WaitBat()
{

}


bool WaitBat::update(float dt, sf::Vector2f pPos)
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

		if (go)
			move(sf::Vector2f(dir * speed * dt, 0.0f));
		else
		{
			float dist = sprite.getPosition().y - pPos.y;
			if (dist < WB_TRIGGER_DIST && dist > -WB_TRIGGER_DIST)
				go = true;
		}

		if (onFire)
			return updateFlame(dt);

		if (isOffscreen())
		{
			despawn();
			return true;
		}
	}
	return false;
}


void WaitBat::activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	// Do activation steps common to all types of enemies
	commonActivate(pos, tile, playerPos);

	go = false;
}

void WaitBat::copy(WaitBat& e)
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
	go = e.go;
	inGravField = e.inGravField;
	distToBH = e.distToBH;
	dirToBH = e.dirToBH;
	distMoved = e.distMoved;
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