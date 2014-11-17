//==========================//
// PlayerProjectiles.h      //
// Author: Matthew Stephens //
//==========================//
#ifndef _PLAYER_PROJECTILES_H_
#define _PLAYER_PROJECTILES_H_

#include <SFML/Graphics.hpp>
#include "EventHandler.h"

class EnemyManager;
class Laser;
class FreezeRay;
class PlayerProjectiles;

//==================================================
// PlayerProjectiles EventHandler for Event::SCROLL
//==================================================
class PPScrollHandler : public EventHandler
{
public:
	// Constructor
	explicit PPScrollHandler(PlayerProjectiles *pp): pPP(pp) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	PlayerProjectiles *pPP;
};

//========================================================
// PlayerProjectiles EventHandler for Event::PLAYER_SHOOT
//========================================================
class PPShootHandler : public EventHandler
{
public:
	// Constructor
	explicit PPShootHandler(PlayerProjectiles *pp): pPP(pp) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	PlayerProjectiles *pPP;
};

//=========================================================
// PlayerProjectiles EventHandler for Event::TM_TRANSITION
//=========================================================
class PPTransitionHandler : public EventHandler
{
public:
	// Constructor
	explicit PPTransitionHandler(PlayerProjectiles *pp): pPP(pp) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	PlayerProjectiles *pPP;
};

class PlayerProjectiles
{
public:
	// Constructor
	PlayerProjectiles();
	// Destructor
	~PlayerProjectiles();

	void init(sf::Texture *l, sf::Texture *fr);
	void clear();
	void scroll(sf::Vector2f ds);

	void checkCollisions(EnemyManager *enemies);
	
	void spawn(sf::Vector2f pos, float dir, int type);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	Laser *lasers;
	FreezeRay *freezeRays;
	int lInd;
	int frInd;
	EventHandler *scrollHandler;
	EventHandler *shootHandler;
	EventHandler *transitionHandler;

    // Helpers
    void remove(int ind, int type);
};

#endif