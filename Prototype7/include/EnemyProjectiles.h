//==========================//
// EnemyProjectiles.h       //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENEMY_PROJECTILES_H_
#define _ENEMY_PROJECTILES_H_

#include <SFML/Graphics.hpp>
#include "EventHandler.h"

class EnemyManager;
class Player;
class AcidSpit;
class EnemyProjectiles;

//==================================================
// EnemyProjectiles EventHandler for Event::SCROLL
//==================================================
class EPScrollHandler : public EventHandler
{
public:
	// Constructor
	explicit EPScrollHandler(EnemyProjectiles *ep): pEP(ep) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	EnemyProjectiles *pEP;
};

//========================================================
// EnemyProjectiles EventHandler for Event::ENEMY_SHOOT
//========================================================
class EPShootHandler : public EventHandler
{
public:
	// Constructor
	explicit EPShootHandler(EnemyProjectiles *ep): pEP(ep) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	EnemyProjectiles *pEP;
};

//=========================================================
// EnemyProjectiles EventHandler for Event::TM_TRANSITION
//=========================================================
class EPTransitionHandler : public EventHandler
{
public:
	// Constructor
	explicit EPTransitionHandler(EnemyProjectiles *ep): pEP(ep) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	EnemyProjectiles *pEP;
};

class EnemyProjectiles
{
public:
	// Constructor
	EnemyProjectiles();
	// Destructor
	~EnemyProjectiles();

	void init(sf::Texture *t);
	void clear();
	void scroll(sf::Vector2f ds);

	void checkCollisions(Player *player);
	
	void spawn(sf::Vector2f pos, float dir, int type);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	AcidSpit *acidSpits;
	int asInd;
	EventHandler *scrollHandler;
	EventHandler *shootHandler;
	EventHandler *transitionHandler;

    // Helpers
    void remove(int ind, int type);
};

#endif