//==========================//
// DeathAnimator.h          //
// Author: Matthew Stephens //
//==========================//
#include "DeathAnimator.h"
#include "Constants.h"
#include "EventManager.h"


void DAEDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_DEATH && e.weaponType != W_GRAVITY_BOMB)
		pDA->startAnimation(e.posX, e.posY, e.dir, e.enemyType);
}

void DAPDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_DEATH)
		pDA->startAnimation(e.posX, e.posY, e.dir, -1);
}

void DAScrollHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::SCROLL)
		pDA->scroll(sf::Vector2f(e.scrollX, e.scrollY));
}

void DATransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION)
		pDA->clear();
}

const int DeathAnimator::MAX_ANIMATIONS = 8;

DeathAnimator::DeathAnimator()
{
	deaths = NULL;
	eDeathHandler = NULL;
	pDeathHandler = NULL;
	scrollHandler = NULL;
	transitionHandler = NULL;
}

DeathAnimator::~DeathAnimator()
{
	if (eDeathHandler)
		delete eDeathHandler;
	if (pDeathHandler)
		delete pDeathHandler;
	if (scrollHandler)
		delete scrollHandler;
	if (transitionHandler)
		delete transitionHandler;
	if (deaths)
		delete [] deaths;
}

void DeathAnimator::init(sf::Texture *t)
{
	deaths = new DeathAnimation[MAX_ANIMATIONS];
	for (int i = 0; i < MAX_ANIMATIONS; i++)
		deaths[i].init(t);
	index = 0;

	pDeath.init(t);

	eDeathHandler = new DAEDeathHandler(this);
	pDeathHandler = new DAPDeathHandler(this);
	scrollHandler = new DAScrollHandler(this);
	transitionHandler = new DATransitionHandler(this);
	EventManager::addHandler(Event::ENEMY_DEATH, eDeathHandler);
	EventManager::addHandler(Event::PLAYER_DEATH, pDeathHandler);
	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
}

void DeathAnimator::startAnimation(float x, float y, float dir, int type)
{
	if (type > -1)
	{
		if (index == MAX_ANIMATIONS)
			return;

		deaths[index].startAnimation(x, y, dir, type);
		index++;
	}
	else
		pDeath.startAnimation(x, y, dir, -1);
}

void DeathAnimator::scroll(sf::Vector2f ds)
{
	for (int i = 0; i < index; i++)
		deaths[i].scroll(ds);
}

void DeathAnimator::update(float dt)
{
	int i = 0;
	while (deaths[i].isInProgress() && i < MAX_ANIMATIONS)
	{
		if (deaths[i].update(dt))
			remove(i);
		else
			i++;
	}

	if (pDeath.isInProgress())
	{
		if (pDeath.update(dt))
		{
			Event::Data e;
			e.type = Event::PLAYER_DEATH_ANIM_DONE;
			EventManager::triggerEvent(e);
		}
	}
}

void DeathAnimator::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < index; i++)
		deaths[i].draw(window);

	if (pDeath.isInProgress())
		pDeath.draw(window);
}

void DeathAnimator::clear()
{
	for (int i = 0; i < index; i++)
		deaths[i].deactivate();
	index = 0;
}

void DeathAnimator::remove(int ind)
{
	int j = MAX_ANIMATIONS - 1;
	while (j > ind && !deaths[j].isInProgress())
		j--;
	deaths[ind].copy(deaths[j]);
	deaths[j].deactivate();
	index--;
}
