//==========================//
// PlayerProjectiles.cpp    //
// Author: Matthew Stephens //
//==========================//
#include "PlayerProjectiles.h"
#include "Laser.h"
#include "EnemyManager.h"
#include "EventManager.h"
#include "Constants.h"
#include "FreezeRay.h"
#include "Flame.h"
#include "GravityBomb.h"
	
void PPScrollHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::SCROLL)
		pPP->scroll(sf::Vector2f(e.scrollX, e.scrollY));
}

	
void PPShootHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_SHOOT)
		pPP->spawn(sf::Vector2f(e.posX, e.posY), e.dir, e.weaponType);
}

void PPTransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION)
		pPP->clear();
}

// Constructor
PlayerProjectiles::PlayerProjectiles()
{
	scrollHandler = NULL;
	shootHandler = NULL;
	transitionHandler = NULL;
	lasers = NULL;
	freezeRays = NULL;
	flame = NULL;
	gBomb = NULL;
}
// Destructor
PlayerProjectiles::~PlayerProjectiles()
{
	if (scrollHandler)
		delete scrollHandler;
	if (shootHandler)
		delete shootHandler;
	if (transitionHandler)
		delete transitionHandler;

	if (lasers)
		delete [] lasers;
	if (freezeRays)
		delete [] freezeRays;
	if (flame)
		delete flame;
	if (gBomb)
		delete gBomb;
}

void PlayerProjectiles::init(sf::Texture *l, sf::Texture *fr, sf::Texture *f, sf::Texture *g)
{
	lasers = new Laser[MAX_LASERS];
	for (int i = 0; i < MAX_LASERS; i++)
	{
		lasers[i].setTexture(l);
		lasers[i].init();
	}
	lInd = 0;

	freezeRays = new FreezeRay[MAX_FREEZE_RAYS];
	for (int i = 0; i < MAX_FREEZE_RAYS; i++)
	{
		freezeRays[i].setTexture(fr);
		freezeRays[i].init();
	}
	frInd = 0;

	flame = new Flame();
	flame->setTexture(f);
	flame->init();

	gBomb = new GravityBomb();
	gBomb->setTexture(g);
	gBomb->init();

	// Register event handlers
	scrollHandler = new PPScrollHandler(this);
	shootHandler = new PPShootHandler(this);
	transitionHandler = new PPTransitionHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::PLAYER_SHOOT, shootHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
}
	
void PlayerProjectiles::spawn(sf::Vector2f pos, float dir, int type)
{
	switch (type)
	{
	case W_LASER:
		if (lInd == MAX_LASERS)
			return;
		lasers[lInd].activate(pos, dir);
		lInd++;
		break;
	case W_FREEZE_RAY:
		if (frInd == MAX_FREEZE_RAYS)
			return;
		freezeRays[frInd].activate(pos, dir);
		frInd++;
		break;
	case W_FLAMETHROWER:
		flame->activate(pos, dir);
		break;
	case W_GRAVITY_BOMB:
		if (gBomb->isReady())
			gBomb->activate(pos, dir);
		break;
	default:
		break;
	}
}

void PlayerProjectiles::checkCollisions(EnemyManager *enemies)
{
	//std::ofstream log("log.txt", std::ios::app);


	int i = 0;
	while (lasers[i].isActive() && i < MAX_LASERS)
		//if (enemies->checkCollisions(&lasers[i]))
		if (enemies->checkCollisions((Entity*)&lasers[i], W_LASER))
            remove(i, W_LASER);
		else
            i++;

	i = 0;
	while (freezeRays[i].isActive() && i < MAX_FREEZE_RAYS)
		//if (enemies->checkCollisions(&freezeRays[i]))
		if (enemies->checkCollisions((Entity*)&freezeRays[i], W_FREEZE_RAY))
            remove(i, W_FREEZE_RAY);
		else
            i++;

	if (flame->isActive())
		//enemies->checkCollisions(flame);
		enemies->checkCollisions((Entity*)flame, W_FLAMETHROWER);
}

void PlayerProjectiles::clear()
{
	// Clear any active lasers
	for (int i = 0; i < lInd; i++)
		lasers[i].deactivate();
	lInd = 0;

	// Clear any active freeze rays
	for (int i = 0; i < frInd; i++)
		freezeRays[i].deactivate();
	frInd = 0;

	if (gBomb->isActive())
		gBomb->deactivate();
}

void PlayerProjectiles::scroll(sf::Vector2f ds)
{
	// Scroll any active lasers
	int i = 0;
	while (lasers[i].isActive() && i < MAX_LASERS)
		lasers[i++].scroll(ds);

	// Scroll any active freeze rays
	i = 0;
	while (freezeRays[i].isActive() && i < MAX_FREEZE_RAYS)
		freezeRays[i++].scroll(ds);

	if (gBomb->isActive())
		gBomb->scroll(ds);
}

void PlayerProjectiles::update(float dt)
{
	int i = 0;
	float dir;
	bool offScreenRight, offScreenLeft;

	// Update any lasers on screen
	while (lasers[i].isActive() && i < MAX_LASERS)
	{
		dir = lasers[i].getDir();
		lasers[i].move(sf::Vector2f(dir * lasers[i].getSpeed() * dt, 0.0f));

        // If laser is offscreen, deactivate it
        offScreenRight = lasers[i].getPosition().x > SCREEN_WIDTH;
        offScreenLeft = lasers[i].getPosition().x < 0.0f - lasers[i].getHitbox().width;
        if (offScreenRight || offScreenLeft)
            remove(i, W_LASER);
		else
            i++;
	}

	// Update any freeze rays on screen
	while (freezeRays[i].isActive() && i < MAX_FREEZE_RAYS)
	{
		if (freezeRays[i].update(dt))
			remove(i, W_FREEZE_RAY);
		else
		{
			dir = freezeRays[i].getDir();
			freezeRays[i].move(sf::Vector2f(dir * freezeRays[i].getSpeed() * dt, 0.0f));

			// If laser is offscreen, deactivate it
			offScreenRight = freezeRays[i].getPosition().x > SCREEN_WIDTH;
			offScreenLeft = freezeRays[i].getPosition().x < 0.0f - freezeRays[i].getHitbox().width;
			if (offScreenRight || offScreenLeft)
				remove(i, W_FREEZE_RAY);
			else
				i++;
		}
	}

	if (flame->isActive())
		flame->update(dt);

	if (gBomb->isActive())
		gBomb->update(dt);


}

void PlayerProjectiles::draw(sf::RenderWindow& window)
{
	//int i = 0;
	//while (lasers[i].isActive())
	for (int i = 0; i < lInd; i++)
		lasers[i].draw(window);
	
	//i = 0;
	//while (freezeRays[i].isActive())
	for (int i = 0; i < frInd; i++)
		freezeRays[i].draw(window);

	if (flame->isActive())
		flame->draw(window);

	if (gBomb->isActive())
		gBomb->draw(window);

}

void PlayerProjectiles::remove(int ind, int type)
{
	int j;

	switch (type)
	{
	case W_LASER:
		//lasers[ind].deactivate();
		j = MAX_LASERS - 1;
		while (j > ind && !lasers[j].isActive())
			j--;
		lasers[ind].copy(lasers[j]);
		lasers[j].deactivate();
		lInd--;
		break;
	case W_FREEZE_RAY:
		j = MAX_FREEZE_RAYS - 1;
		while (j > ind && !freezeRays[j].isActive())
			j--;
		freezeRays[ind].copy(freezeRays[j]);
		freezeRays[j].deactivate();
		frInd--;
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