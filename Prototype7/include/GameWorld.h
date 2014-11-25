//==========================//
// GameWorld.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _GAME_WORLD_H_
#define _GAME_WORLD_H_

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Constants.h"
#include "TileMap.h"
#include <string>
#include "EventHandler.h"
#include "Background.h"

class Game;
class GameWorld;

class Transition
{
public:
	Transition() {}

	int tileMapID;
	sf::Vector2i entryTile;
	sf::Vector2i referenceTile;
	int reposition;
};

class MapSection
{
public:
	MapSection() {}

	TileMap map;
	int bkgdID;
	int bkgdScale;
};


//=================================================
// GameWorld EventHandler for Event::TM_TRANSITION
//=================================================
class GWTransitionHandler : public EventHandler
{
public:
	//Constructor
	GWTransitionHandler(GameWorld *gw): pGW(gw) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	GameWorld *pGW;
};

//============================================
// GameWorld EventHandler for Event::CONTINUE
//============================================
class GWContinueHandler : public EventHandler
{
public:
	//Constructor
	GWContinueHandler(GameWorld *gw): pGW(gw) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	GameWorld *pGW;
};

//=============================================
// GameWorld EventHandler for Event::ENEMY_DEATH
//=============================================
class GWEnemyDeathHandler : public EventHandler
{
public:
	//Constructor
	explicit GWEnemyDeathHandler(GameWorld *gw): pGW(gw) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	GameWorld *pGW;
};

//==========================================
// GameWorld EventHandler for Event::SCROLL
//==========================================
class GWScrollHandler : public EventHandler
{
public:
	//Constructor
	explicit GWScrollHandler(GameWorld *gw): pGW(gw) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	GameWorld *pGW;
};

//=======================================================
// GameWorld EventHandler for Event::INITIAL_ENEMY_SPAWN
//=======================================================
class GWInitialSpawnHandler : public EventHandler
{
public:
	//Constructor
	explicit GWInitialSpawnHandler(GameWorld *gw): pGW(gw) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	GameWorld *pGW;
};


class GameWorld
{
public:
	// Constructor
	GameWorld() {}
	// Destructor
	~GameWorld();

	TileMap* getActiveMap();

	// Methods
	void loadFromFile(std::string filename, Game *pGame);
	void init();
	void transition(int entrance);
	void scrollBackground(sf::Vector2f ds);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	MapSection *maps;
	TileMap *activeMap;
	Background *backgrounds;
	Background *activeBkgd;
	int nBkgds;
	int nMaps;
	int nTransitions;
	Transition *transitions;
	//Background background;
	EventHandler *eDeathHandler;
	EventHandler *transitionHandler;
	EventHandler *scrollHandler;
	EventHandler *initialSpawnHandler;
	EventHandler *continueHandler;
};

#endif