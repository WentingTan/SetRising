//==========================//
// DeathAnimator.h          //
// Author: Matthew Stephens //
//==========================//
#ifndef _DEATH_ANIMATOR_H_
#define _DEATH_ANIMATOR_H_

#include "DeathAnimation.h"
#include "EventHandler.h"

// Forward declatarions
class DeathAnimator;

//===================================================
// DeathAnimator EventHandler for Event::ENEMY_DEATH
//===================================================
class DAEDeathHandler : public EventHandler
{
public:
	// Constructor
	explicit DAEDeathHandler(DeathAnimator *da): pDA(da) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	DeathAnimator *pDA;
};

//====================================================
// DeathAnimator EventHandler for Event::PLAYER_DEATH
//====================================================
class DAPDeathHandler : public EventHandler
{
public:
	// Constructor
	explicit DAPDeathHandler(DeathAnimator *da): pDA(da) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	DeathAnimator *pDA;
};

//==============================================
// DeathAnimator EventHandler for Event::SCROLL
//==============================================
class DAScrollHandler : public EventHandler
{
public:
	// Constructor
	explicit DAScrollHandler(DeathAnimator *da): pDA(da) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	DeathAnimator *pDA;
};

//=====================================================
// DeathAnimator EventHandler for Event::TM_TRANSITION
//=====================================================
class DATransitionHandler : public EventHandler
{
public:
	// Constructor
	explicit DATransitionHandler(DeathAnimator *da): pDA(da) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	DeathAnimator *pDA;
};

class DeathAnimator
{
public:
	// Constructor
	DeathAnimator();
	// Destructor
	~DeathAnimator();

	void init(sf::Texture *t);
	void startAnimation(float x, float y, float dir, int type);
	void update(float dt);
	void scroll(sf::Vector2f ds);
	void clear();
	void draw(sf::RenderWindow& window);

private:
	DeathAnimation *deaths;
	int index;

	DeathAnimation pDeath;

	EventHandler *eDeathHandler;
	EventHandler *pDeathHandler;
	EventHandler *scrollHandler;
	EventHandler *transitionHandler;

	void remove(int ind);

	static const int MAX_ANIMATIONS;

};

#endif