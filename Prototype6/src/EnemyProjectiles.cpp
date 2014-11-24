//==========================//
// EnemyProjectiles.cpp     //
// Author: Matthew Stephens //
//==========================//
#include "EnemyProjectiles.h"
#include "AcidSpit.h"
#include "Player.h"
#include "EventManager.h"
#include "Constants.h"
#include <fstream>
void EPScrollHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::SCROLL)
		pEP->scroll(sf::Vector2f(e.scrollX, e.scrollY));
}

	
void EPShootHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_SHOOT)
		pEP->spawn(sf::Vector2f(e.posX, e.posY), e.dir, e.weaponType);
}

void EPTransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION)
		pEP->clear();
}



// Constructor
EnemyProjectiles::EnemyProjectiles()
{
	scrollHandler = NULL;
	shootHandler = NULL;
	transitionHandler = NULL;
	acidSpits = NULL;
}
// Destructor
EnemyProjectiles::~EnemyProjectiles()
{
	if (scrollHandler)
		delete scrollHandler;
	if (shootHandler)
		delete shootHandler;
	if (transitionHandler)
		delete transitionHandler;

	if (acidSpits)
		delete [] acidSpits;
}

void EnemyProjectiles::init(sf::Texture *t)
{
	acidSpits = new AcidSpit[MAX_ACID_SPITS];
	for (int i = 0; i < MAX_ACID_SPITS; i++)
	{
		acidSpits[i].setTexture(t);
		acidSpits[i].init();
	}
	asInd = 0;

	// Register event handlers
	scrollHandler = new EPScrollHandler(this);
	shootHandler = new EPShootHandler(this);
	transitionHandler = new EPTransitionHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::ENEMY_SHOOT, shootHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
}
	
void EnemyProjectiles::spawn(sf::Vector2f pos, float dir, int type)
{
	switch (type)
	{
	case W_ACID_SPIT:
		if (asInd == MAX_ACID_SPITS)
			return;
		acidSpits[asInd].activate(pos, dir);
		asInd++;
		break;
	default:
		break;
	}
}

void EnemyProjectiles::checkCollisions(Player *player)
{
	Event::Data e;
	e.type = Event::PLAYER_HIT;

	int i = 0;
	while (acidSpits[i].isActive())
	{
		if (acidSpits[i].getHitbox().intersects(player->getHitBox()))
		{
			player->damage(acidSpits[i].getDamage());
			remove(i, W_ACID_SPIT);
			return;
		}
		i++;
	}
}

void EnemyProjectiles::clear()
{
	// Clear any active acid spits
	for (int i = 0; i < asInd; i++)
		acidSpits[i].deactivate();
	asInd = 0;
}

void EnemyProjectiles::scroll(sf::Vector2f ds)
{
	// Scroll any active acid spits
	int i = 0;
	while (acidSpits[i].isActive() && i < MAX_ACID_SPITS)
		acidSpits[i++].scroll(ds);
}

void EnemyProjectiles::update(float dt)
{
	int i = 0;
	float dir;
	bool offScreenRight, offScreenLeft;

	// Update any acid spits on screen
	while (acidSpits[i].isActive() && i < MAX_ACID_SPITS)
	{
		dir = acidSpits[i].getDir();
		acidSpits[i].move(sf::Vector2f(dir * acidSpits[i].getSpeed() * dt, 0.0f));

        // If acid spit is offscreen, deactivate it
        offScreenRight = acidSpits[i].getPosition().x > SCREEN_WIDTH;
        offScreenLeft = acidSpits[i].getPosition().x < 0.0f - acidSpits[i].getHitbox().width;
        if (offScreenRight || offScreenLeft)
            remove(i, W_ACID_SPIT);
		else
            i++;
	}

}

void EnemyProjectiles::draw(sf::RenderWindow& window)
{
	// Draw active acid spits to the screen
	int i = 0;
	while (acidSpits[i].isActive())
		acidSpits[i++].draw(window);
}

void EnemyProjectiles::remove(int ind, int type)
{
	int j;

	switch (type)
	{
	case W_ACID_SPIT:
		j = MAX_ACID_SPITS - 1;
		while (j > ind && !acidSpits[j].isActive())
			j--;
		acidSpits[ind].copy(acidSpits[j]);
		acidSpits[j].deactivate();
		asInd--;
		break;
	default:
		break;
	}
 
	/*
    // Maintain "sorted" order, i.e. all active lasers are before inactive ones
    while (j < k)
	{
        while (lasers[j].isActive() && j < 9)
            j++;
        while (!lasers[k].isActive() && k > 0)
            k--;
        if (j < k)
		{
            lasers[j].copy(lasers[k]);
            lasers[k].deactivate();
		}
	}
    lInd--;
	*/
}