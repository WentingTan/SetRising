//==========================//
// Enemy.cpp                //
// Author: Matthew Stephens //
//==========================//
#include "Enemy.h"

#include <fstream>
#include "AlphaOscillator.h"
#include "EventManager.h"
#include "Constants.h"
#include "Flame.h"
#include "FreezeRay.h"
#include "Laser.h"
#include "Player.h"


Enemy::Enemy(int type, float maxHealth):
	GravEntity(),
	type(type),
	freezeBlinker(255, 0, 0.125f),
	MAX_HEALTH(maxHealth)
{
	extraHB = NULL;
	perFrameHBCoords = NULL;
}

Enemy::~Enemy()
{
	if (extraHB)
		delete [] extraHB;
	if (perFrameHBCoords)
		delete [] perFrameHBCoords;
}

void Enemy::init(std::string filename)
{
	std::ifstream file(filename.c_str());

	// Read in the dimensions of the sprite
	file >> imgDim.x;
	file >> imgDim.y;

	// Read in the starting and ending frame for animation
	file >> startFrame;
	file >> endFrame;
	// Read in the time per frame for animation
	file >> frameTime;

	// Read in the number of additional hitboxes
	file >> nExtraHBs;

	// Allocate storage for additional hitboxes
	extraHB = new sf::FloatRect[nExtraHBs];

	// Allocate storage for an array that contains the hitbox offsets
	// per frame
	int nPFHBC = (nExtraHBs + 1) * (endFrame - startFrame + 1);
	perFrameHBCoords = new sf::FloatRect[nPFHBC];

	// Read in the per frame hitbox coordinates
	for (int i = 0; i < nPFHBC; i++)
	{
		file >> perFrameHBCoords[i].left;
		file >> perFrameHBCoords[i].top;
		file >> perFrameHBCoords[i].width;
		file >> perFrameHBCoords[i].height;
	}

	file.close();

	// Set the texture and texture rect
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, imgDim.x, imgDim.y));

	// Set the origin to the center of the sprite
	sprite.setOrigin(0.5f * (float)imgDim.x, 0.5f * (float)imgDim.y);
}


void Enemy::deactivate()
{
	active = false;
}

void Enemy::burn()
{
	flameTimer = 0.0f;
	onFire = true;
	frozen = false;
	sprite.setColor(sf::Color::Red);
}

void Enemy::freeze()
{
	frozen = true;
	sprite.setColor(sf::Color::Blue);
	freezeTimer = 0.0f;
}

void Enemy::unfreeze()
{
	frozen = false;
	sprite.setColor(sf::Color::White);
}

//====================================================
// SnakeEnemy::isFrozen()
// Indicates whether or not the SnakeEnemy is frozen.
//====================================================
bool Enemy::isFrozen() const
{
	return frozen;
}

//===============================================================
// Enemy::getSpawnTile()
// Returns the index of the tile at which the enemy was spawned.
//===============================================================
sf::Vector2i Enemy::getSpawnTile() const
{
	return spawnTile;
}

//=================================
// Enemy::updateFreeze(float)
//=================================
void Enemy::updateFreeze(float dt)
{
	freezeTimer += dt;
		
	if (freezeTimer > FREEZE_TIME)
		unfreeze();
	else if (freezeTimer > 0.75f * FREEZE_TIME)
	{
		freezeBlinker.update(dt);
		sprite.setColor(sf::Color(freezeBlinker.getAlpha(), freezeBlinker.getAlpha(), 255));
	}
}

bool Enemy::updateFlame(float dt)
{
	float amount = flameTimer > 0.0f ? 0.2f * FLAME_DAMAGE * dt : FLAME_DAMAGE * dt;
	
	flameTimer += dt;

	if (flameTimer > FLAME_TIME)
	{
		onFire = false;
		sprite.setColor(sf::Color::White);
	}

	if (damage(amount))
	{
		kill(W_FLAMETHROWER);
		return true;
	}
	else
		return false;
}

//=========================================================================================
// Enemy::checkCollision(Laser*)
// Checks for a collision between the enemy and the laser. If a collision is detected, the
// enemy is damaged.  If the damage results in the enemy's health falling below 0, then an
// ENEMY_DEATH event is generated (by the call to kill()) and the method returns true,
// returns false otherwise.
//=========================================================================================
bool Enemy::checkCollision(Laser* l, bool& collide)
{
	sf::FloatRect hb = l->getHitbox();
	collide = false;

	// First check the main hitbox
	if (hitbox.intersects(hb))
	{
		collide = true;
		if (damage(LASER_DAMAGE))
		{
			kill(W_LASER);
			return true;
		}
		return false;
	}

	// If no collision with main hitbox, check additional hitboxes if any
	for (int i = 0; i < nExtraHBs; i++)
	{
		if (extraHB[i].intersects(hb))
		{
			collide = true;
			if (damage(LASER_DAMAGE))
			{
				kill(W_LASER);
				return true;
			}
			return false;
		}
	}

	// No collisions/no death
	return false;
}

//======================================================================================
// Enemy::checkCollision(Flame*)
// Checks for a collision between the enemy and the flame. If a collision is dectected,
// the burn() method is called, which sets the 'onFire' flag to apply flame damage over
// time.
//======================================================================================
void Enemy::checkCollision(Flame *f)
{
	sf::FloatRect hb = f->getHitbox();

	// First check the main hitbox
	if (hitbox.intersects(hb))
	{
		burn();
		return;
	}

	// If no collision with main hitbox, check additional hitboxes if any
	for (int i = 0; i < nExtraHBs; i++)
	{
		if (extraHB[i].intersects(hb))
		{
			burn();
			return;
		}
	}
}

//===========================================================================================
// Enemy::checkCollision(FreezeRay*)
// Checks for a collision between the enemy and the freeze ray. If a collision is detected
// and the enemy is not frozen, the enemy is frozen and no damage is done. If there is a
// collision and the enemy is already frozen, the enemy is unfrozen and takes damage. If the
// damage results in the enemy's health falling below 0, then an ENEMY_DEATH event is
// generated (by the call to kill()) and the method returns true, returns false otherwise.
//===========================================================================================
bool Enemy::checkCollision(FreezeRay* fr, bool& collide)
{
	sf::FloatRect hb = fr->getHitbox();
	collide = false;

	// First check the main hitbox
	if (hitbox.intersects(hb))
	{
		collide = true;
		if (!frozen)
			freeze();
		else
		{
			unfreeze();
			if (damage(FREEZE_DAMAGE))
			{
				kill(W_FREEZE_RAY);
				return true;
			}
		}
		return false;
	}

	// If no collision with main hitbox, check additional hitboxes if any
	for (int i = 0; i < nExtraHBs; i++)
	{
		if (extraHB[i].intersects(hb))
		{
			collide = true;
			if (!frozen)
				freeze();
			else
			{
				unfreeze();
				if (damage(FREEZE_DAMAGE))
				{
					kill(W_FREEZE_RAY);
					return true;
				}
			}
			return false;
		}
	}

	// No collisions/no death
	return false;
}

bool Enemy::checkCollision(Player *p, sf::FloatRect& overlap) const
{
	sf::FloatRect hb = p->getHitBox();

	// Check for collisions with main hitbox
	if (hitbox.intersects(hb, overlap))
		return true;

	// If no collision with main hitbox, check additional hitboxes if any
	for (int i = 0; i < nExtraHBs; i++)
	{
		if (extraHB[i].intersects(hb, overlap))
			return true;
	}

	// No collisions
	return false;
}



//=========================================================================================
// Enemy::updateGravity(float)
// Updates an enemy that is the gravitational field of a blackhole. The current distance
// to the blackhole is calculated and used to determine the speed and scale of the enemy.
// Generates an ENEMY_DEATH event and returns true when the enemy has been sucked into the
// blackhole, false otherwise.
//=========================================================================================
bool Enemy::updateGravity(float dt)
{
	if (GravEntity::updateGravity(dt))
	{
		kill(W_GRAVITY_BOMB);
		return true;
	}
	else
		return false;
}

//=================================
// Enemy::kill(int)
// Generates an ENEMY_DEATH event.
//=================================
void Enemy::kill(int weapon)
{
	Event::Data e;
	e.type = Event::ENEMY_DEATH;
	e.enemyType = type;
	e.weaponType = weapon;
	e.posX = sprite.getPosition().x;
	e.posY = sprite.getPosition().y;
	e.tile = spawnTile;
	e.dir = dir;

	EventManager::triggerEvent(e);
}

//==============================================================================
// Enemy::animate(float)
// Animates the enemy sprite and updates the hitbox based on the current frame.
//==============================================================================
void Enemy::animate(float dt)
{
	animTimer += dt;

	//sf::FloatRect bounds = sprite.getGlobalBounds();
	sf::IntRect rect = sf::IntRect(0, 0, imgDim.x, imgDim.y);

	if (animTimer > frameTime)
	{
		if (++frame > endFrame)
			frame = startFrame;

		rect.left = frame * imgDim.x;
		sprite.setTextureRect(rect);
		animTimer = 0.0f;

		// Update hitboxes based on the current frame of animation
		updateHitboxes();
	}
}

bool Enemy::damage(float amount)
{
	health -= amount;
	if (health <= 0.0f)
		return true;
	else
		return false;
}
void Enemy::commonActivate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos)
{
	// Select a random frame to start the animation
	frame = startFrame + (int)(((float)rand() / RAND_MAX) * (float)(endFrame - startFrame + 1));
	animTimer = 0.0f;
	frozen = false;
	onFire = false;
	inGravField = false;
	freezeTimer = 0.0f;
	flameTimer = 0.0f;
	sprite.setColor(sf::Color::White);
	sprite.setRotation(0.0f);

	// Determine the direction the enemy should face
	dir = pos.x - playerPos.x > 0.0f ? D_LEFT : D_RIGHT;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sf::IntRect rect = sf::IntRect(frame * (int)bounds.width, 0, (int)bounds.width, (int)bounds.height);
	sprite.setTextureRect(rect);

	//pos.y -= 0.5f * 94.0f;
	sprite.setPosition(pos);
	spawnTile = tile;
	health = MAX_HEALTH;
	active = true;

	// Update hitboxes based on the frame of animation and location
	updateHitboxes();

	// Scale the sprite so it is facing the correct direction
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


void Enemy::move(sf::Vector2f ds)
{
	sprite.move(ds);

	// Update main hitbox
	hitbox.left += ds.x;
	hitbox.top += ds.y;

	// Update aditional hitboxes if any
	for (int i = 0; i < nExtraHBs; i++)
	{
		extraHB[i].left += ds.x;
		extraHB[i].top += ds.y;
	}
}

void Enemy::scroll(sf::Vector2f ds)
{
	sprite.move(-1.0f * ds);

	// Update main hitbox
	hitbox.left -= ds.x;
	hitbox.top -= ds.y;

	// Update aditional hitboxes if any
	for (int i = 0; i < nExtraHBs; i++)
	{
		extraHB[i].left -= ds.x;
		extraHB[i].top -= ds.y;
	}
}

void Enemy::updateHitboxes()
{
	// Update the main hitbox
	sf::Vector2f pos = sprite.getPosition();
	sf::FloatRect hbOffset = perFrameHBCoords[(frame - startFrame) * (nExtraHBs + 1)];
	hitbox.top = pos.y - hbOffset.top;
	hitbox.left = pos.x + ((dir == 1.0f ? -hbOffset.width : 0.0f) + dir * hbOffset.left);
	hitbox.width = hbOffset.width;
	hitbox.height = hbOffset.height;

	// Update additional hitboxes if any
	for (int i= 0; i < nExtraHBs; i++)
	{
		hbOffset = perFrameHBCoords[(frame - startFrame) * (nExtraHBs + 1) + i + 1];
		extraHB[i].top = pos.y - hbOffset.top;
		extraHB[i].left = pos.x + ((dir == 1.0f ? -hbOffset.width : 0.0f) + dir * hbOffset.left);
		extraHB[i].width = hbOffset.width;
		extraHB[i].height = hbOffset.height;
	}
}