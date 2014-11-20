//==========================//
// GravEntity.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _GRAV_ENTITY_H_
#define _GRAV_ENTITY_H_

#include "Entity.h"

// Forward declarations
class Blackhole;

class GravEntity : public Entity
{
public:
	// Constructor
	GravEntity();
	// Destructor
	virtual ~GravEntity();

	// Accessors
	bool isInGravField() const;

	// Methods
	void checkCollisionBH(Blackhole *bh);

protected:
	float dir;
	bool inGravField;
	float distToBH;
	sf::Vector2f dirToBH;
	float distMoved;
	float speed;

	// Helpers
	bool updateGravity(float dt);
};

#endif