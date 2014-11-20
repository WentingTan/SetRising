//==========================//
// GravEntity.cpp           //
// Author: Matthew Stephens //
//==========================//
#include "GravEntity.h"

#include <fstream>
#include <math.h>
#include "EventManager.h"
#include "Constants.h"
#include "Blackhole.h"


GravEntity::GravEntity():
	Entity()
{
	// Do nothing
}

GravEntity::~GravEntity()
{
	// Do nothing
}

bool GravEntity::isInGravField() const
{
	return inGravField;
}

//=============================================================================
// GravEntity::checkCollision(Blackhole*)
// Checks if the entity is within range of the blackhole's graviational field.
//=============================================================================
void GravEntity::checkCollisionBH(Blackhole *bh)
{
	// Get the position and field radius of the blackhole
	sf::Vector2f pos = bh->getPosition();
	float r = bh->getFieldRadius();

	// Calculate distance to blackhole
	sf::Vector2f diff = pos - sprite.getPosition();
	distToBH = sqrt(diff.x * diff.x + diff.y * diff.y);

	if (distToBH < r)
	{
		// Increase the number of objects in the blackhole's field
		bh->incInField();

		// Enemy is in the grav field of the blackhole
		inGravField = true;

		// Calculate and store the normalized vector to the blakchole
		dirToBH = diff / distToBH;
		distMoved = 0.0f;
	}
}

//=========================================================================================
// GravEntity::updateGravity(float)
// Updates an enemy that is the gravitational field of a blackhole. The current distance
// to the blackhole is calculated and used to determine the speed and scale of the enemy.
// Returns true if the object has been sucked into the blackhole, false otherwise.
//=========================================================================================
bool GravEntity::updateGravity(float dt)
{
	float r = distToBH - distMoved;

	if (r > 0.15f * distToBH)
	{
		float fallSpeed = GRAV_CONST / r;
		if (fallSpeed < speed)
			fallSpeed = speed;

		sprite.rotate(2.0f * fallSpeed * dt);
		sf::Vector2f ds = fallSpeed * dt * dirToBH;
		move(sf::Vector2f(ds.x, ds.y));

		distMoved +=  sqrt(ds.x * ds.x + ds.y * ds.y);

		float scale = 1.0f - ((1.0f / distToBH) * distMoved);
		sprite.setScale(dir * scale, scale);

		return false;
	}
	else
		return true;
}