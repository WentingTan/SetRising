//==========================//
// Entity.cpp               //
// Author: Matthew Stephens //
//==========================//
#include "Entity.h"

//=============================================
// Entity Constructor()
// The entity is created in an inactive state.
//=============================================
Entity::Entity()
{
	active = false;
}

//===================
// Entity Destructor
//===================
Entity::~Entity()
{

}

//===========//
// Accessors //
//===========//

//===========================================================
// Entity::getPosition()
// Returns the position of the entity in screen coordinates.
//===========================================================
sf::Vector2f Entity::getPosition() const
{
	return sprite.getPosition();
}

//===================================
// Entity::getHitbox()
// Returns the hitbox of the entity.
//===================================
sf::FloatRect Entity::getHitbox() const
{
	return hitbox;
}

//================================================================
// Entity::isActive()
// Returns a bool indicating whether the entity is active or not.
//================================================================
bool Entity::isActive() const
{
	return active;
}


//==========//
// Mutators //
//==========//

//==================================================================================
// Entity::setTexture(sf::Texture*)
// Sets the texture of te entity.  It is assumed that the texture pointed to by 't'
// has already been loaded.
//==================================================================================
void Entity::setTexture(sf::Texture *t)
{
	texture = t;
}

//========================================================
// Entity::setPosition(sf::Vector2f)
// Sets the position of the entity to the given position.
//========================================================
void Entity::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

//==================================================================================
// Entity::scroll(sf::Vector2f)
// Scrolls the entity in the direction opposite the given vector.  Also updates the
// entity's hitbox.
//==================================================================================
void Entity::scroll(sf::Vector2f ds)
{
	sprite.move(-1.0f * ds);

	hitbox.left -= ds.x;
	hitbox.top -= ds.y;
}

//=======================================================================
// Entity::move(sf::Vector2f)
// Moves the entity by the given amount and updates the entity's hitbox.
//=======================================================================
void Entity::move(sf::Vector2f ds)
{
	sprite.move(ds);

	hitbox.left += ds.x;
	hitbox.top += ds.y;
}


//=========//
// Methods //
//=========//

//=============================================
// Entity::draw(sf::RenderWindow&)
// Draws the entity to the given RenderWindow.
//=============================================
void Entity::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

//=================================================================================
// Entity::collidesWith(Entity*)
// Returns a bool indicating whether or not the entity is currently colliding with
// the given Entity.
//=================================================================================
bool Entity::collidesWith(Entity *other) const
{
	return hitbox.intersects(other->hitbox);
}

//=================================================================================
// Entity::collidesWith(Entity*, sf::FloatRect&)
// Returns a bool indicating whether or not the entity is currently colliding with
// the given Entity. Fills the given FloatRect with the rectangle of intersection.
//=================================================================================
bool Entity::collidesWith(Entity *other, sf::FloatRect& overlap) const
{
	return hitbox.intersects(other->hitbox, overlap);
}
