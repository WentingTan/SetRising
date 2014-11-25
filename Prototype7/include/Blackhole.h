//==========================//
// Blackhole.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _BLACK_HOLE_H
#define _BLACK_HOLE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EventHandler.h"

class Blackhole;

//==========================================
// Blackhole EventHandler for Event::SCROLL
//==========================================
class BHScrollHandler : public EventHandler
{
public:
	// Constructor
	explicit BHScrollHandler(Blackhole *bh): pBH(bh) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Blackhole *pBH;
};

//=================================================
// Blackhole EventHandler for Event::TM_TRANSITION
//=================================================
class BHTransitionHandler : public EventHandler
{
public:
	// Constructor
	explicit BHTransitionHandler(Blackhole *bh): pBH(bh) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	Blackhole *pBH;
};

//=====================================================
// Blackhole EventHandler for Event::GRAV_BOMB_IMPLODE
//=====================================================
class BHImplodeHHandler : public EventHandler
{
public:
	// Constructor
	explicit BHImplodeHHandler(Blackhole *bh): pBH(bh) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	Blackhole *pBH;
};

//===============================================
// Blackhole EventHandler for Event::ENEMY_DEATH
//===============================================
class BHDeathHandler : public EventHandler
{
public:
	// Constructor
	explicit BHDeathHandler(Blackhole *bh): pBH(bh) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	Blackhole *pBH;
};

class Blackhole : public Entity
{
public:
	// Constructor
	Blackhole();
	// Destructor
	~Blackhole();

	// Accessors
	float getFieldRadius() const;

	// Methods
	void init();
	void activate(sf::Vector2f pos);
    void deactivate();
	void update(float dt);
	void incInField();
	void decInField();
	void draw(sf::RenderWindow& window);
	//void scroll(sf::Vector2f ds);

private:
	int nInField;
	float timer;
	float radius;
	sf::CircleShape hole;

	EventHandler *implodeHandler;
	EventHandler *scrollHandler;
	EventHandler *deathHandler;
	EventHandler *transitionHandler;
};

#endif