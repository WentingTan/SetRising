//==========================//
// PickupManager.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "PickupManager.h"
#include "EventManager.h"
#include "Player.h"
#include "Pickup.h"
#include "WeaponPickup.h"

//===============================================================================
// PMScrollHandler::handleEvent(Event::Data)
// Handles Event::SCROLL by calling PickupManager::scroll() through its internal
// PickupManager pointer.
//===============================================================================
void PMScrollHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::SCROLL)
		pPM->scroll(sf::Vector2f(e.scrollX, e.scrollY));
}

//=====================================================================================
// PMTransitionHandler::handleEvent(Event::Data)
// Handles Event::TM_TRASNITION by calling PickupManager::clear() through its internal
// PickupManager pointer. This clears all pickups from the screen.  Also used on game
// over.
//=====================================================================================
void PMTransitionHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::TM_TRANSITION || e.type == Event::PLAYER_DEATH_ANIM_DONE)
		pPM->clear();
}

//=================================================================================
// PMEDeathHandler::handleEvent(Event::Data)
// Handles Event::ENEMY_DEATH. Rolls a random number to determine if a pickup will
// be spawned as a result of the enemy death, and if so, accomplishes this through
// a call to PickupManager::spawn().
//=================================================================================
void PMEDeathHandler::handleEvent(Event::Data e)
{
	float r;
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::ENEMY_DEATH)
	{
		// Get a random number
		r = (float)rand() / (float)RAND_MAX;

		// 30% chance to spawn a pickup
		if (r < 0.3f)
			pPM->spawn(sf::Vector2f(e.posX, e.posY), pPM->getRandomType(), pPM->getRandomSize());
	}
}

void PMSpawnWeaponHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::SPAWN_WEAPON)
	{
		pPM->setWeaponSpawnTile(e.tile, e.pickupType);
		pPM->spawn(sf::Vector2f(e.posX, e.posY), e.pickupType, P_SMALL);
	}
}

// Constructor
PickupManager::PickupManager()
{
	spawnHandler = NULL;
	transitionHandler =NULL;
	eDeathHandler = NULL;
	scrollHandler = NULL;
}
	// Destructor
PickupManager::~PickupManager()
{
	if (spawnHandler)
		delete spawnHandler;
	if (transitionHandler)
		delete transitionHandler;
	if (eDeathHandler)
		delete eDeathHandler;
	if (scrollHandler)
		delete scrollHandler;
}

int PickupManager::getRandomType()
{
	float r = (float)rand() / RAND_MAX;

	if (hasFreeze)
		return (int)((float)(P_FREEZE_E - P_HEALTH + 1) * r);
	else if (hasFlame)
		return (int)((float)(P_FLAME_E - P_HEALTH + 1) * r);
	else
		return (int)((float)(P_GRAV_BOMB - P_HEALTH + 1) * r);
}

//============================================================================
// PickupManager::getRandomSize()
// Returns a randomly selected size of a pickup.  75% for a small pickup, 25%
// chance for a large pickup.
//============================================================================
float PickupManager::getRandomSize()
{
	float r = (float)rand() / RAND_MAX;

	if (r < 0.75f)
		return P_SMALL;
	else
		return P_LARGE;
}

void PickupManager::setWeaponSpawnTile(sf::Vector2i tile, int type)
{
	if (type == P_FLAMETHROWER)
		flamethrower->setSpawnTile(tile);
	else if (type == P_FREEZERAY)
		freezeray->setSpawnTile(tile);
}

//========================================================================
// PickupManager::init(sf::Texture*)
// Allocates space for an array of 10 HealthPickups. Sets the texture and
// initializes each pickup in the array.  Initializes and registers event
// handlers.
//========================================================================
void PickupManager::init(sf::Texture *hp, sf::Texture *gp, sf::Texture *ep)
{

	hasFlame = false;
	hasFreeze = false;

	healthPickups = new Pickup[MAX_PICKUPS];
	for (int i = 0; i < MAX_PICKUPS; i++)
	{
		healthPickups[i].setTexture(hp);
		healthPickups[i].init(P_HEALTH);
	}
	hpInd = 0;

	gravPickups = new Pickup[MAX_PICKUPS];
	for (int i = 0; i < MAX_PICKUPS; i++)
	{
		gravPickups[i].setTexture(gp);
		gravPickups[i].init(P_GRAV_BOMB);
	}
	gpInd = 0;

	flamePickups = new Pickup[MAX_PICKUPS];
	for (int i = 0; i < MAX_PICKUPS; i++)
	{
		flamePickups[i].setTexture(ep);
		flamePickups[i].init(P_FLAME_E);
	}
	flInd = 0;

	freezePickups = new Pickup[MAX_PICKUPS];
	for (int i = 0; i < MAX_PICKUPS; i++)
	{
		freezePickups[i].setTexture(ep);
		freezePickups[i].init(P_FREEZE_E);
	}
	frInd = 0;

	flamethrower = new WeaponPickup();
	flamethrower->setTexture(ep);
	flamethrower->init(P_FLAMETHROWER);

	freezeray = new WeaponPickup();
	freezeray->setTexture(ep);
	freezeray->init(P_FREEZERAY);

	scrollHandler = new PMScrollHandler(this);
	eDeathHandler = new PMEDeathHandler(this);
	transitionHandler = new PMTransitionHandler(this);
	spawnHandler = new PMSpawnWeaponHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::ENEMY_DEATH, eDeathHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
	EventManager::addHandler(Event::SPAWN_WEAPON, spawnHandler);
	EventManager::addHandler(Event::PLAYER_DEATH_ANIM_DONE, transitionHandler);
}

//================================================================================
// PickupManager::spawn(sf::Vector2f,int)
//
//================================================================================
void PickupManager::spawn(sf::Vector2f pos, int type, float size)
{
	switch (type)
	{
	case P_HEALTH:
		if (hpInd == MAX_PICKUPS)
			return;
		healthPickups[hpInd].activate(pos, size);
		hpInd++;
		break;
	case P_GRAV_BOMB:
		if (gpInd == MAX_PICKUPS)
			return;
		gravPickups[gpInd].activate(pos, P_SMALL);
		gpInd++;
		break;
	case P_FLAME_E:
		if (flInd == MAX_PICKUPS)
			return;
		flamePickups[flInd].activate(pos, size);
		flInd++;
		break;
	case P_FREEZE_E:
		if (frInd == MAX_PICKUPS)
			return;
		freezePickups[frInd].activate(pos, size);
		frInd++;
		break;
	case P_FLAMETHROWER:
		flamethrower->activate(pos, size);
		break;
	case P_FREEZERAY:
		freezeray->activate(pos, size);
		break;
	default:
		break;
	}
}

//=====================================
// PickupManager::scroll(sf::Vector2f)
// Scrolls all of the active pickups
//=====================================
void PickupManager::scroll(sf::Vector2f ds)
{
	for (int i = 0; i < hpInd; i++)
		healthPickups[i].scroll(ds);

	for (int i= 0; i < gpInd; i++)
		gravPickups[i].scroll(ds);

	for (int i= 0; i < flInd; i++)
		flamePickups[i].scroll(ds);

	for (int i= 0; i < frInd; i++)
		freezePickups[i].scroll(ds);

	if (flamethrower->isActive())
		flamethrower->scroll(ds);
	if (freezeray->isActive())
		freezeray->scroll(ds);

}

//==============================================================================
// PickupManager::checkCollisions(Player*)
// Checks for collisions between active pickups and the player.  If a collision
// is detected, a PLAYER_HEAL event is generated and the pickup is deactivated
// for re-use later.
//==============================================================================
void PickupManager::checkCollisions(Player *player)
{
	int i = 0;
	while (healthPickups[i].isActive() && i < MAX_PICKUPS)
	{
		if (healthPickups[i].getHitbox().intersects(player->getHitBox()))
		{
			player->getPickup(P_HEALTH, healthPickups[i].getSize());
			remove(i, P_HEALTH);
		}
		else
			i++;
	}

	i = 0;
	while (gravPickups[i].isActive() && i < MAX_PICKUPS)
	{
		if (gravPickups[i].getHitbox().intersects(player->getHitBox()))
		{
			player->getPickup(P_GRAV_BOMB, 0);
			remove(i, P_GRAV_BOMB);
		}
		else
			i++;
	}

	i = 0;
	while (flamePickups[i].isActive() && i < MAX_PICKUPS)
	{
		if (flamePickups[i].getHitbox().intersects(player->getHitBox()))
		{
			player->getPickup(P_FLAME_E, flamePickups[i].getSize());
			remove(i, P_FLAME_E);
		}
		else
			i++;
	}

	i = 0;
	while (freezePickups[i].isActive() && i < MAX_PICKUPS)
	{
		if (freezePickups[i].getHitbox().intersects(player->getHitBox()))
		{
			player->getPickup(P_FREEZE_E, freezePickups[i].getSize());
			remove(i, P_FREEZE_E);
		}
		else
			i++;
	}

	if (flamethrower->isActive() && flamethrower->getHitbox().intersects(player->getHitBox()))
	{
		player->getPickup(P_FLAMETHROWER, 0);
		hasFlame = true;
		flamethrower->deactivate();
	}

	if (freezeray->isActive() && freezeray->getHitbox().intersects(player->getHitBox()))
	{
		player->getPickup(P_FREEZERAY, 0);
		hasFreeze = true;
		freezeray->deactivate();
	}
}

//====================================
// PickupManager::update(float)
// Updates all of the active pickups.
//====================================
void PickupManager::update(float dt)
{
	int i = 0;
	while (healthPickups[i].isActive() && i < MAX_PICKUPS)
	{
		if (healthPickups[i].update(dt))
			remove(i, P_HEALTH);
		else
			i++;
	}

	i = 0;
	while (gravPickups[i].isActive() && i < MAX_PICKUPS)
	{
		if (gravPickups[i].update(dt))
			remove(i, P_GRAV_BOMB);
		else
			i++;
	}

	i = 0;
	while (flamePickups[i].isActive() && i < MAX_PICKUPS)
	{
		if (flamePickups[i].update(dt))
			remove(i, P_FLAME_E);
		else
			i++;
	}

	i = 0;
	while (freezePickups[i].isActive() && i < MAX_PICKUPS)
	{
		if (freezePickups[i].update(dt))
			remove(i, P_FREEZE_E);
		else
			i++;
	}
}

//===================================================
// PickupManager::clear()
// Clears all of the health pickups from the screen.
//===================================================
void PickupManager::clear()
{
	for (int i = 0; i < hpInd; i++)
		healthPickups[i].deactivate();
	hpInd = 0;

	for (int i = 0; i < gpInd; i++)
		gravPickups[i].deactivate();
	gpInd = 0;

	for (int i = 0; i < flInd; i++)
		flamePickups[i].deactivate();
	flInd = 0;

	for (int i = 0; i < frInd; i++)
		freezePickups[i].deactivate();
	frInd = 0;

	if (flamethrower->isActive())
		flamethrower->despawn();

	if (freezeray->isActive())
		freezeray->despawn();
}

//===================================================================
// PickupManager::draw(sf::RenderWindow&)
// Draws all of the active HealthPickups in the array to the window.
//===================================================================
void PickupManager::draw(sf::RenderWindow& window)
{	
	for (int i = 0; i < hpInd; i++)
		healthPickups[i].draw(window);

	for (int i = 0; i < gpInd; i++)
		gravPickups[i].draw(window);

	for (int i = 0; i < flInd; i++)
		flamePickups[i].draw(window);

	for (int i = 0; i < frInd; i++)
		freezePickups[i].draw(window);

	if (flamethrower->isActive())
		flamethrower->draw(window);

	if (freezeray->isActive())
		freezeray->draw(window);
}

//============================================================================
// PickupManager::remove(int, int)
// Helper method that "removes" the pickup at the given index.  The object is
// not actually removed from the array but it is removed from action as it is
// deactivated and moved to a higher index in the array to allow all active
// pickups to be at lower indices, thereby maintaining a semi-sorted order.
//============================================================================
void PickupManager::remove(int ind, int type)
{
    //healthPickups[ind].deactivate();
    int j = MAX_PICKUPS - 1;

	switch (type)
	{
	case P_HEALTH:
		while (j > ind && !healthPickups[j].isActive())
			j--;
		healthPickups[ind].copy(healthPickups[j]);
		healthPickups[j].deactivate();
		hpInd--;
		break;
	case P_GRAV_BOMB:
		while (j > ind && !gravPickups[j].isActive())
			j--;
		gravPickups[ind].copy(gravPickups[j]);
		gravPickups[j].deactivate();
		gpInd--;
		break;
	case P_FLAME_E:
		while (j > ind && !flamePickups[j].isActive())
			j--;
		flamePickups[ind].copy(flamePickups[j]);
		flamePickups[j].deactivate();
		flInd--;
		break;
	case P_FREEZE_E:
		while (j > ind && !freezePickups[j].isActive())
			j--;
		freezePickups[ind].copy(freezePickups[j]);
		freezePickups[j].deactivate();
		frInd--;
		break;
	default:
		break;
	}
}