//==========================//
// PickupManager.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "PickupManager.h"
#include "EventManager.h"
#include "Player.h"
#include "GravPickup.h"

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
// PickupManager pointer. This clears all pickups from the screen.
//=====================================================================================
void PMTransitionHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::TM_TRANSITION)
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
	int type;
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::ENEMY_DEATH)
	{
		// Get a random number
		r = (float)rand() / (float)RAND_MAX;

		// 30% chance to spawn a pickup
		if (r < 0.3f)
		{
			// Get another random number to determine pickup type
			r = (float)rand() / (float)RAND_MAX;

			// 50% chance small pickup
			if (r < 0.5f)
				type = SM_HEALTH;
			// 25% chance large pickup
			else if (r < 0.75f)
				type = LG_HEALTH;
			// 25% chance of gravity bomb
			else
				type = GRAV_BOMB;

			// Spawn the pickup
			pPM->spawn(sf::Vector2f(e.posX, e.posY), type);
		}
	}
}


// Constructor
PickupManager::PickupManager()
{

}
	// Destructor
PickupManager::~PickupManager()
{

}

//========================================================================
// PickupManager::init(sf::Texture*)
// Allocates space for an array of 10 HealthPickups. Sets the texture and
// initializes each pickup in the array.  Initializes and registers event
// handlers.
//========================================================================
void PickupManager::init(sf::Texture *hp, sf::Texture *gp)
{
	healthPickups = new HealthPickup[MAX_HEALTH_PICKUPS];
	for (int i = 0; i < MAX_HEALTH_PICKUPS; i++)
	{
		healthPickups[i].setTexture(hp);
		healthPickups[i].init();
	}
	hpInd = 0;

	gravPickups = new GravPickup[MAX_GRAV_PICKUPS];
	for (int i = 0; i < MAX_GRAV_PICKUPS; i++)
	{
		gravPickups[i].setTexture(gp);
		gravPickups[i].init();
	}
	gpInd = 0;

	scrollHandler = new PMScrollHandler(this);
	eDeathHandler = new PMEDeathHandler(this);
	transitionHandler = new PMTransitionHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::ENEMY_DEATH, eDeathHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
}

//================================================================================
// PickupManager::spawn(sf::Vector2f,int)
//
//================================================================================
void PickupManager::spawn(sf::Vector2f pos, int type)
{
	switch (type)
	{
	case SM_HEALTH:
	case LG_HEALTH:
		if (hpInd == MAX_HEALTH_PICKUPS)
			return;
		healthPickups[hpInd].activate(pos, type);
		hpInd++;
		break;
	case GRAV_BOMB:
		if (gpInd == MAX_GRAV_PICKUPS)
			return;
		gravPickups[gpInd].activate(pos);
		gpInd++;
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
		healthPickups[i++].scroll(ds);

	for (int i= 0; i < gpInd; i++)
		gravPickups[i].scroll(ds);

}

//==============================================================================
// PickupManager::checkCollisions(Player*)
// Checks for collisions between active pickups and the player.  If a collision
// is detected, a PLAYER_HEAL event is generated and the pickup is deactivated
// for re-use later.
//==============================================================================
void PickupManager::checkCollisions(Player *player)
{
	Event::Data e;

	e.type = Event::PLAYER_HEAL;
	int i = 0;
	while (healthPickups[i].isActive())
	{
		if (healthPickups[i].getHitbox().intersects(player->getHitBox()))
		{
			e.health = healthPickups[i].getHealth();
			EventManager::triggerEvent(e);
			remove(i, SM_HEALTH);
		}
		else
			i++;
	}

	e.type = Event::GRAV_PICKUP;
	i = 0;
	while (gravPickups[i].isActive())
	{
		if (gravPickups[i].getHitbox().intersects(player->getHitBox()))
		{
			EventManager::triggerEvent(e);
			remove(i, GRAV_BOMB);
		}
		else
			i++;
	}
}

//====================================
// PickupManager::update(float)
// Updates all of the active pickups.
//====================================
void PickupManager::update(float dt)
{
	int i = 0;
	while (healthPickups[i].isActive() && i < MAX_HEALTH_PICKUPS)
	{
		if (healthPickups[i].update(dt))
			remove(i, SM_HEALTH);
		else
			i++;
	}

	i = 0;
	while (gravPickups[i].isActive() && i < MAX_GRAV_PICKUPS)
	{
		if (gravPickups[i].update(dt))
			remove(i, GRAV_BOMB);
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
    int j;

	switch (type)
	{
	case SM_HEALTH:
	case LG_HEALTH:
		j = MAX_HEALTH_PICKUPS - 1;
		while (j > ind && !healthPickups[j].isActive())
			j--;
		healthPickups[ind].copy(healthPickups[j]);
		healthPickups[j].deactivate();
		hpInd--;
		break;
	case GRAV_BOMB:
		j = MAX_GRAV_PICKUPS - 1;
		while (j > ind && !gravPickups[j].isActive())
			j--;
		gravPickups[ind].copy(gravPickups[j]);
		gravPickups[j].deactivate();
		gpInd--;
		break;
	default:
		break;
	}
}