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


class PickupManager
{
public:
	// Constructor
	PickupManager();
	// Destructor
	~PickupManager();

	// Methods
	void init(sf::Texture *t);
	void checkCollisions(Player *player);
	void scroll(sf::Vector2f ds);
	void spawn(sf::Vector2f pos, int size, sf::Vector2i tile);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	HealthPickup *healthPickups;
	int index;
	EventHandler *scrollHandler;
	EventHandler *eDeathHandler;

	// Helper
	void remove(int ind);
};

#endif