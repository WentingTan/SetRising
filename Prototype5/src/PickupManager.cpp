//==========================//
// PickupManager.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "PickupManager.h"
#include "EventManager.h"
#include "Player.h"

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
	int size;
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

			// 70% chance small pickup
			if (r < 0.7f)
				size = 0;
			// 30% chance large pickup
			else
				size = 1;

			// Spawn the pickup
			pPM->spawn(sf::Vector2f(e.posX, e.posY), size, sf::Vector2i(0,0));
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
void PickupManager::init(sf::Texture *t)
{
	healthPickups = new HealthPickup[10];
	for (int i = 0; i < 10; i++)
	{
		healthPickups[i].setTexture(t);
		healthPickups[i].init();
	}
	index = 0;

	scrollHandler = new PMScrollHandler(this);
	eDeathHandler = new PMEDeathHandler(this);
	transitionHandler = new PMTransitionHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::ENEMY_DEATH, eDeathHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
}

//================================================================================
// PickupManager::spawn(sf::Vector2f,int,sf::Vector2i)
// Spawns a HealthPickup of the given 'size' at the given position. If this was
// spawned by the TileMap, 'tile' will contain the tile index of the spawn point,
// otherwise, the pickup was spawned by an enemy death and 'tile' will be (0,0).
//================================================================================
void PickupManager::spawn(sf::Vector2f pos, int size, sf::Vector2i tile)
{
	healthPickups[index].activate(pos, size, tile);
	index++;
}

//=======================================================
// PickupManager::scroll(sf::Vector2f)
// Scrolls all of the active HealthPickups in the array.
//=======================================================
void PickupManager::scroll(sf::Vector2f ds)
{
	int i = 0;
	while (healthPickups[i].isActive())
		healthPickups[i++].scroll(ds);
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
			remove(i);
		}
		else
			i++;
	}
}

//=======================================================
// PickupManager::update(float)
// Updates all of the active HealthPickups in the array.
//=======================================================
void PickupManager::update(float dt)
{
	int i = 0;
	while (healthPickups[i].isActive())
	{
		if (healthPickups[i].update(dt))
			remove(i);
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
	for (int i = 0; i < index; i++)
		healthPickups[i].deactivate();
	index = 0;
}

//===================================================================
// PickupManager::draw(sf::RenderWindow&)
// Draws all of the active HealthPickups in the array to the window.
//===================================================================
void PickupManager::draw(sf::RenderWindow& window)
{
	int i = 0;
	while (healthPickups[i].isActive())
		healthPickups[i++].draw(window);
}

//============================================================================
// PickupManager::remove(int)
// Helper method that "removes" the pickup at the given index.  The object is
// not actually removed from the array but it is removed from action as it is
// deactivated and moved to a higher index in the array to allow all active
// pickups to be at lower indices, thereby maintaining a semi-sorted order.
//============================================================================
void PickupManager::remove(int ind)
{
    healthPickups[ind].deactivate();
    int j = 9;

    // Maintain "sorted" order, i.e. all active pickups are before inactive ones
	// Find the last active pickup in the array and swap places with the one being
	// deactivated
    while (j > ind && !healthPickups[j].isActive())
		j--;
	healthPickups[ind].swap(healthPickups[j]);

	// Decrement the count of active pickups
	index--;
}