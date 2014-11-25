//==========================//
// PatrollingSnake.cpp      //
// Author: Matthew Stephens //
//==========================//
#include "PatrollingSnake.h"

#include "Event.h"
#include "EventManager.h"
#include "Constants.h"
#include "TileMap.h"


PatrollingSnake::PatrollingSnake():
	Snake(E_PATROLLING_SNAKE)
{
	speed = SNAKE_SPEED;
	// Set the maximum patrol distance to a third of the screen width
	maxPatrolDist = 0.333f * SCREEN_WIDTH;
}

PatrollingSnake::~PatrollingSnake()
{

}

void PatrollingSnake::updatePatrol(float dt, TileMap *map)
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

// returns true if the patrolling snake has been killed
bool PatrollingSnake::update(float dt, TileMap *map)
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

		shootTimer += dt;
		//std::ofstream log("log.txt", std::ios::app);
		//log << "Patrolling Snake update: shootTmer = " << shootTimer << "\n";
			//log.close();
		if (shootTimer > nextShootTime)
		{
			shoot();
			shootTimer = 0.0f;
			nextShootTime = getNextShootTime(PS_SHOOT_TIME_LO, PS_SHOOT_TIME_HI);
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

//=================================================================================
// PatrollingSnake::activate(sf::Vector2f, sf::Vector2i, sf::Vector2f)
// Activates the patrolling snake. First calls SnakeEnemy::commonActivate(), which
// performs activation tasks common to both types of snake enmies. Then performs
// activation tasks specific to the patrolling snake: setting the patrol distance
// to 0, and getting the next shoot time.
//=================================================================================
void PatrollingSnake::activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	// Do activation steps common to both types of snake enemies
	Snake::activate(pos, tile, playerPos);

	shootTimer = 0.0f;
	patrolDist = 0.0f;
	nextShootTime = getNextShootTime(0.8f * PS_SHOOT_TIME_LO, 0.8f * PS_SHOOT_TIME_HI);
}

void PatrollingSnake::copy(PatrollingSnake& e)
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
	nextShootTime = e.nextShootTime;
	patrolDist = e.patrolDist;
	flameTimer = e.flameTimer;
	onFire = e.onFire;
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


//============================================================================================
// Enemy::checkFloorEdge()
// Checks if the bottom corner (based on direction) of the enemy's hitbox is colliding with a
// solid tile.  Returns true if it is, false otherwise.
//============================================================================================
bool PatrollingSnake::checkFloorEdge(TileMap *map)
{
	// First make sure the snake is in contact with a floor
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
