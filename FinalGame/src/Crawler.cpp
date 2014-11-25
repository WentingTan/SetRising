//==========================//
// Crawler.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "Crawler.h"

#include <fstream>
#include "Event.h"
#include "EventManager.h"
#include "Constants.h"
#include "TileMap.h"


Crawler::Crawler():
	Enemy(E_CRAWLER, CRAWLER_HEALTH)
{
	speed = CRAWLER_SPEED;
	maxPatrolDist = 0.4f * SCREEN_WIDTH;
}

Crawler::~Crawler()
{
	// Do nothing
}

void Crawler::init()
{
	Enemy::init(CRAWLER_FILE);
}

void Crawler::activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	commonActivate(pos, tile, playerPos);
	move(sf::Vector2f(0.0f, -0.375f * hitbox.height));
	patrolDist = 0.0f;
}

bool Crawler::update(float dt, TileMap *map)
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
		updatePatrol(dt, map);

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

void Crawler::copy(Crawler& c)
{
    texture = c.texture;
	sprite = c.sprite;
	hitbox = c.hitbox;
	active = c.active;
    spawnTile = c.spawnTile;
	health = c.health;
	dir = c.dir;
	frame = c.frame;
	animTimer = c.animTimer;
	frozen = c.frozen;
	freezeTimer = c.freezeTimer;
	patrolDist = c.patrolDist;
	flameTimer = c.flameTimer;
	onFire = c.onFire;
	inGravField = c.inGravField;
	distToBH = c.distToBH;
	dirToBH = c.dirToBH;
	distMoved = c.distMoved;
}

void Crawler::updatePatrol(float dt, TileMap *map)
{
	move(sf::Vector2f(dir * speed * dt, 0.0f));
	patrolDist += speed * dt;

	if (!checkFloorEdge(map) || patrolDist >= maxPatrolDist)
	{
		patrolDist = 0.0f;
		dir *= -1.0f;
		sprite.setScale(dir, 1.0f);
	}
}

bool Crawler::checkFloorEdge(TileMap *map)
{
	// First make sure the crawler is in contact with a floor
	while (!isTouchingFloor(map))
		Enemy::move(sf::Vector2f(0.0f, 1.0f));

	// Get the coordinates of the bottom corner of the enemy's hitbox
	sf::Vector2f corner;
	corner.y = hitbox.top + hitbox.height;
	corner.x = hitbox.left + (dir == D_LEFT ? 0.0f : hitbox.width);

	// Get the tile index of the tile at those screen corrdinates
	sf::Vector2i index = map->getTileIndex(corner.x, corner.y);

	// Return true if the tile is solid, false otherwise
	if (map->indexIsWithinBounds(index.x, index.y))
		return map->isTileObstacle(index.x, index.y);
	else
		return false;
}