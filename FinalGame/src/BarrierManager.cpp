//==========================//
// BarrierManager.h          //
// Author: Matthew Stephens //
//==========================//
#include "BarrierManager.h"
#include "IceBlock.h"
#include "Constants.h"
#include "EventManager.h"
#include "Laser.h"
#include "FreezeRay.h"
#include "Flame.h"
#include "Player.h"

const int BarrierManager::MAX_ICEBLOCKS = 16;

void BMScrollHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::SCROLL)
		pBM->scroll(sf::Vector2f(e.scrollX, e.scrollY));
}

void BMTransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION || e.type == Event::PLAYER_DEATH_ANIM_DONE)
		pBM->clear();
}

void BMSpawnHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::SPAWN_BARRIER)
		pBM->spawn(sf::Vector2f(e.posX, e.posY), e.tile);
}

BarrierManager::BarrierManager()
{
	iceBlocks = NULL;
	scrollHandler = NULL;
	transitionHandler = NULL;
	spawnHandler = NULL;
}

BarrierManager::~BarrierManager()
{
	if (scrollHandler)
		delete scrollHandler;
	if (transitionHandler)
		delete transitionHandler;
	if (spawnHandler)
		delete spawnHandler;
	if (iceBlocks)
		delete [] iceBlocks;
}

void BarrierManager::init(sf::Texture *t)
{
	iceBlocks = new IceBlock[MAX_ICEBLOCKS];
	for (int i = 0; i < MAX_ICEBLOCKS; i++)
	{
		iceBlocks[i].setTexture(t);
		iceBlocks[i].init();
	}
	index = 0;

	scrollHandler = new BMScrollHandler(this);
	transitionHandler = new BMTransitionHandler(this);
	spawnHandler = new BMSpawnHandler(this);
	EventManager::addHandler(Event::SPAWN_BARRIER, spawnHandler);
	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
	EventManager::addHandler(Event::PLAYER_DEATH_ANIM_DONE, transitionHandler);
}

bool BarrierManager::checkCollisions(Player *p, sf::FloatRect& overlap)
{
	for (int i = 0; i < index; i++)
		if (iceBlocks[i].checkCollision(p, overlap))
			return true;

	return false;
}

bool BarrierManager::checkFloorBlocks(Player *p)
{
	sf::FloatRect hb = p->getHitBox();
	sf::FloatRect overlap;

	for (int i = 0; i < index; i++)
	{
		if (iceBlocks[i].checkCollision(p, overlap) && overlap.width > 1.0f)
		{
			p->move(0.0f, -overlap.height + 1.0f);
			return true;
		}
	}

	return false;
}

bool BarrierManager::checkWallBlocks(Player *p)
{
	sf::FloatRect hb = p->getHitBox();
	float dir = p->getDir();
	sf::FloatRect overlap;

	for (int i = 0; i < index; i++)
	{
		if (iceBlocks[i].checkCollision(p, overlap) && overlap.height > 2.5f)
		{
			p->move(-dir * overlap.width, 0.0f);
			return true;
		}
	}

	return false;
}

bool BarrierManager::checkCeilingBlocks(Player *p)
{
	sf::FloatRect hb = p->getHitBox();
	sf::FloatRect overlap;

	for (int i = 0; i < index; i++)
	{
		if (iceBlocks[i].checkCollision(p, overlap) && overlap.width > 1.0f && overlap.top < hb.top + 0.25f * hb.height)
		{
			p->move(0.0f, overlap.height + 0.5f);
			return true;
		}
	}

	return false;
}

bool BarrierManager::checkCollisions(Laser *laser)
{
	for (int i = 0; i < index; i++)
		if (iceBlocks[i].checkCollision(laser))
			return true;

	return false;
}

bool BarrierManager::checkCollisions(FreezeRay *fRay)
{
	for (int i = 0; i < index; i++)
		if (iceBlocks[i].checkCollision(fRay))
			return true;

	return false;
}

void BarrierManager::checkCollisions(Flame *f)
{
	for (int i = 0; i < index; i++)
		iceBlocks[i].checkCollision(f);
}

void BarrierManager::spawn(sf::Vector2f pos, sf::Vector2i tile)
{

	if (index == MAX_ICEBLOCKS)
		return;

	iceBlocks[index].activate(pos, tile);
	index++;
}

void BarrierManager::scroll(sf::Vector2f ds)
{
	for (int i = 0; i < index; i++)
		iceBlocks[i].scroll(ds);
}

void BarrierManager::update(float dt)
{
	int i = 0;
	while (iceBlocks[i].isActive() && i < MAX_ICEBLOCKS)
	{
		if (iceBlocks[i].update(dt))
			remove(i);
		else
			i++;
	}
}

void BarrierManager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < index; i++)
		iceBlocks[i].draw(window);
}

void BarrierManager::clear()
{
	for (int i = 0; i < index; i++)
		iceBlocks[i].despawn();
	index = 0;
}

void BarrierManager::remove(int ind)
{
	iceBlocks[ind].despawn();

	int j = MAX_ICEBLOCKS - 1;
	while (j > ind && !iceBlocks[j].isActive())
		j--;
	iceBlocks[ind].copy(iceBlocks[j]);
	iceBlocks[j].deactivate();
	index--;
}
