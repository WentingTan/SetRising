//==========================//
// StationarySnake.cpp      //
// Author: Matthew Stephens //
//==========================//
#include "Boss.h"

#include "Event.h"
#include "EventManager.h"
#include "Constants.h"
#include <fstream>

Boss::Boss() :
Snake(E_BOSS)
{
	speed = 0.0f;
}

Boss::~Boss()
{

}

void Boss::init()
{
	imgDim.x = 300;
	imgDim.y = 300;

	// Read in the starting and ending frame for animation
	startFrame = 0;
	endFrame = 2;
	// Read in the time per frame for animation
	frameTime = .7;

	// Read in the number of additional hitboxes
	nExtraHBs = 0;

	// Allocate storage for additional hitboxes
	extraHB = new sf::FloatRect[nExtraHBs];

	// Allocate storage for an array that contains the hitbox offsets
	// per frame
	int nPFHBC = (nExtraHBs + 1) * (endFrame - startFrame + 1);
	perFrameHBCoords = new sf::FloatRect[nPFHBC];

	/*
	// Read in the per frame hitbox coordinates
	for (int i = 0; i < nPFHBC; i++)
	{
		file >> perFrameHBCoords[i].left;
		file >> perFrameHBCoords[i].top;
		file >> perFrameHBCoords[i].width;
		file >> perFrameHBCoords[i].height;
	}

	file.close();
	*/
	// Set the texture and texture rect
	perFrameHBCoords[0].left = 16;
	perFrameHBCoords[0].top = 16;
	perFrameHBCoords[0].width = 140;
	perFrameHBCoords[0].height = 140;

	perFrameHBCoords[1].left = 16;
	perFrameHBCoords[1].top = 16;
	perFrameHBCoords[1].width = 140;
	perFrameHBCoords[1].height = 140;

	perFrameHBCoords[2].left = 16;
	perFrameHBCoords[2].top = 16;
	perFrameHBCoords[2].width = 140;
	perFrameHBCoords[2].height = 140;
	
	
	
	
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, imgDim.x, imgDim.y));
	// Set the origin to the center of the sprite
	sprite.setOrigin(0.5f * (float)imgDim.x, 0.5f * (float)imgDim.y);
}

bool Boss::update(float dt, sf::Vector2f pPos)
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

		if (onFire)
			return updateFlame(dt);
	}
	return false;

}


//=================================================================================
// StationarySnake::activate(sf::Vector2f, sf::Vector2i, sf::Vector2f)
// Activates the patrolling snake. First calls SnakeEnemy::commonActivate(), which
// performs activation tasks common to both types of snake enmies. Then performs
// activation tasks specific to the stationary snake: setting the number of fired
// shots to 0, and getting the next shoot time.
//=================================================================================
void Boss::activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	// Do activation steps common to both types of snake enemies
//	Snake::activate(pos, tile, playerPos);

	commonActivate(pos, tile, playerPos);
	move(sf::Vector2f(0.0f, -0.5f * 200.0f));

	shootTimer = 0.0f;
	shots = 0;
	nextShootTime = getNextShootTime(SS_SHOOT_TIME_LO, SS_SHOOT_TIME_HI);
}

void Boss::copy(Boss& e)
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
	onFire = e.onFire;
	flameTimer = e.flameTimer;
	freezeTimer = e.freezeTimer;
	shootTimer = e.shootTimer;
	shots = e.shots;
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