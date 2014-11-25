//==========================//
// BarrierManager.h         //
// Author: Matthew Stephens //
//==========================//
#ifndef _BARRIER_MANAGER_H_
#define _BARRIER_MANAGER_H_

#include <SFML/Graphics.hpp>
#include "EventHandler.h"

// Forward Declarations
class IceBlock;
class Laser;
class FreezeRay;
class Flame;
class Player;
class BarrierManager;

//===============================================
// BarrierManager EventHandler for Event::SCROLL
//===============================================
class BMScrollHandler : public EventHandler
{
public:
	// Constructor
	explicit BMScrollHandler(BarrierManager *bm): pBM(bm) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	BarrierManager *pBM;
};

//=====================================================
// PickupManager EventHandler for Event::TM_TRASNITION
//=====================================================
class BMTransitionHandler : public EventHandler
{
public:
	// Constructor
	explicit BMTransitionHandler(BarrierManager *bm): pBM(bm) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	BarrierManager *pBM;
};


//=====================================================
// PickupManager EventHandler for Event::SPAWN_BARRIER
//=====================================================
class BMSpawnHandler : public EventHandler
{
public:
	// Constructor
	explicit BMSpawnHandler(BarrierManager *bm): pBM(bm) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	BarrierManager *pBM;
};

class BarrierManager
{
public:
	// Constructor
	BarrierManager();
	// Destructor
	~BarrierManager();

	// Methods
	void init(sf::Texture *t);
	bool checkCollisions(Player *p, sf::FloatRect& overlap);
	bool checkCollisions(Laser *laser);
	bool checkCollisions(FreezeRay *fRay);
	void checkCollisions(Flame *f);

	bool checkFloorBlocks(Player *p);
	bool checkWallBlocks(Player *p);
	bool checkCeilingBlocks(Player *p);

	void scroll(sf::Vector2f ds);
	void spawn(sf::Vector2f pos, sf::Vector2i tile);
	void update(float dt);
	void clear();
	void draw(sf::RenderWindow& window);

private:
	IceBlock *iceBlocks;
	int index;

	EventHandler *scrollHandler;
	EventHandler *transitionHandler;
	EventHandler *spawnHandler;

	// Helper
	void remove(int ind);

	static const int MAX_ICEBLOCKS;
};

#endif