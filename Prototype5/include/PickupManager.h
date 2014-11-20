//==========================//
// PickupManager.h          //
// Author: Matthew Stephens //
//==========================//
#ifndef _PICKUP_MANAGER_H_
#define _PICKUP_MANAGER_H_

#include <SFML/Graphics.hpp>
#include "HealthPickup.h"
#include "EventHandler.h"

// Forward Declarations
class GravPickup;
class Player;
class PickupManager;

//==============================================
// PickupManager EventHandler for Event::SCROLL
//==============================================
class PMScrollHandler : public EventHandler
{
public:
	// Constructor
	explicit PMScrollHandler(PickupManager *pm): pPM(pm) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	PickupManager *pPM;
};

//===================================================
// PickupManager EventHandler for Event::ENEMY_DEATH
//===================================================
class PMEDeathHandler : public EventHandler
{
public:
	// Constructor
	explicit PMEDeathHandler(PickupManager *pm): pPM(pm) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	PickupManager *pPM;
};

//=====================================================
// PickupManager EventHandler for Event::TM_TRASNITION
//=====================================================
class PMTransitionHandler : public EventHandler
{
public:
	// Constructor
	explicit PMTransitionHandler(PickupManager *pm): pPM(pm) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	PickupManager *pPM;
};

class PickupManager
{
public:
	// Constructor
	PickupManager();
	// Destructor
	~PickupManager();

	// Methods
	void init(sf::Texture *hp, sf::Texture *gp);
	void checkCollisions(Player *player);
	void scroll(sf::Vector2f ds);
	void spawn(sf::Vector2f pos, int type);
	void update(float dt);
	void clear();
	void draw(sf::RenderWindow& window);

private:
	HealthPickup *healthPickups;
	GravPickup *gravPickups;
	int hpInd;
	int gpInd;
	EventHandler *scrollHandler;
	EventHandler *eDeathHandler;
	EventHandler *transitionHandler;

	// Helper
	void remove(int ind, int type);
};

#endif