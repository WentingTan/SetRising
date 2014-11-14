//==========================//
// Entity.h                 //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENTITY_H
#define _ENTITY_H

#include <SFML/Graphics.hpp>

// The Entity class is a base class used for deriving classes that represent game entities that may interact with eachother.
// It's purpose is to provide basic code that all entities share. It is not meant to provide an interface that may be used
// polymorphically, so none of the Entity class methods are virtual. Each deriving class should supply its own class-specific
// methods, such as an init().
class Entity
{
public:
	// Constructor
	Entity();
	// Destructor
	~Entity();

	// Accessors
	sf::Vector2f getPosition() const;
	sf::FloatRect getHitbox() const;
	bool isActive() const;
	
	// Mutators
	void setTexture(sf::Texture *t);
	void setPosition(sf::Vector2f pos);
	void scroll(sf::Vector2f ds);
	void move(sf::Vector2f ds);
	
	// Methods
	void draw(sf::RenderWindow& window);
	bool collidesWith(Entity *other) const;
	bool collidesWith(Entity *other, sf::FloatRect& overlap) const;

protected:
	sf::Texture *texture;
	sf::Sprite sprite;
	sf::FloatRect hitbox;
	bool active;
};

#endif