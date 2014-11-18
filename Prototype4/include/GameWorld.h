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


// Move TileMap EventHandlers here


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


class GameWorld
{
public:
	// Constructor
	GameWorld() {}
	// Destructor
	~GameWorld() {}

	TileMap* getActiveMap();

	// Methods
	void loadFromFile(std::string filename, Game *pGame);
	void init();
	void transition(int entrance);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	TileMap *maps;
	TileMap *activeMap;
	int nMaps;
	int nTransitions;
	Transition *transitions;
	EventHandler *eDeathHandler;
	EventHandler *transitionHandler;
};

#endif