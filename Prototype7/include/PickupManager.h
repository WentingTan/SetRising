//==========================//
// PickupManager.h          //
// Author: Matthew Stephens //
//==========================//
#ifndef _PICKUP_MANAGER_H_
#define _PICKUP_MANAGER_H_

#include <SFML/Graphics.hpp>
#include "EventHandler.h"

// Forward Declarations
class Pickup;
class Player;
class PickupManager;
class WeaponPickup;

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

//====================================================
// PickupManager EventHandler for Event::SPAWN_WEAPON
//====================================================
class PMSpawnWeaponHandler : public EventHandler
{
public:
	// Constructor
	explicit PMSpawnWeaponHandler(PickupManager *pm): pPM(pm) {}
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
	void init(sf::Texture *hp, sf::Texture *gp, sf::Texture *ep);
	void checkCollisions(Player *player);
	void scroll(sf::Vector2f ds);
	void spawn(sf::Vector2f pos, int type, float size);
	void setWeaponSpawnTile(sf::Vector2i tile, int type);
	void hasAcquiredWeapon(int type);
	void update(float dt);
	void clear();
	int getRandomType();
	float getRandomSize();
	void draw(sf::RenderWindow& window);

private:
	Pickup *healthPickups;
	Pickup *gravPickups;
	Pickup *flamePickups;
	Pickup *freezePickups;
	WeaponPickup *flamethrower;
	WeaponPickup *freezeray;

	int hpInd;
	int gpInd;
	int flInd;
	int frInd;

	bool hasFlame;
	bool hasFreeze;

	EventHandler *scrollHandler;
	EventHandler *eDeathHandler;
	EventHandler *transitionHandler;
	EventHandler *spawnHandler;

	// Helper
	void remove(int ind, int type);
};

#endif