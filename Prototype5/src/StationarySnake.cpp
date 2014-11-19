//==========================//
// StationarySnake.cpp      //
// Author: Matthew Stephens //
//==========================//
#include "StationarySnake.h"

#include "Event.h"
#include "EventManager.h"
#include "Constants.h"


StationarySnake::StationarySnake():
	SnakeEnemy()
{
	// Do nothing
}

StationarySnake::~StationarySnake()
{

}


void StationarySnake::update(float dt, sf::Vector2f pPos)
{
	if (frozen)
		updateFreeze(dt);
	else
	{
		animate(dt);

		if (doFlameDamage)
			updateFlame(dt);

		shootTimer += dt;
		if (shootTimer > nextShootTime)
		{
			shots++;
			shoot();
			shootTimer = 0.0f;

			if (shots < SS_NUM_SHOTS_IN_BURST)
				nextShootTime = SS_BURST_TIME;
			else
			{
				nextShootTime = getNextShootTime(SS_SHOOT_TIME_LO, SS_SHOOT_TIME_HI);
				shots = 0;
			}
		}


		dir = sprite.getPosition().x - pPos.x > 0.0f ? D_LEFT : D_RIGHT;
		sprite.setScale(dir, 1.0f);
	}


}


//=================================================================================
// StationarySnake::activate(sf::Vector2f, sf::Vector2i, sf::Vector2f)
// Activates the patrolling snake. First calls SnakeEnemy::commonActivate(), which
// performs activation tasks common to both types of snake enmies. Then performs
// activation tasks specific to the stationary snake: setting the number of fired
// shots to 0, and getting the next shoot time.
//=================================================================================
void StationarySnake::activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	// Do activation steps common to both types of snake enemies
	commonActivate(pos, tile, playerPos);

	shots = 0;
	nextShootTime = getNextShootTime(SS_SHOOT_TIME_LO, SS_SHOOT_TIME_HI);
}

void StationarySnake::copy(StationarySnake& e)
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
	shootTimer = e.shootTimer;
	shots = e.shots;
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