//==========================//
// GameWorld.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "GameWorld.h"
#include "Game.h"
#include <fstream>
#include "EventManager.h"

//=================
// 
void GWEnemyDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_DEATH || e.type == Event::DESPAWN_ENEMY)
		pGW->getActiveMap()->resetEnemySpawnPoint(e.tile, e.enemyType);
}


void GWTransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION)
		pGW->transition(e.entrance);
}

void GWScrollHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::SCROLL)
		pGW->scrollBackground(sf::Vector2f(e.scrollX, e.scrollY));
}

void GWInitialSpawnHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::INITIAL_ENEMY_SPAWN)
		pGW->getActiveMap()->initialSpawn();
}

TileMap* GameWorld::getActiveMap()
{
	return activeMap;
}

GameWorld::~GameWorld()
{
	if (eDeathHandler)
		delete eDeathHandler;
	if (transitionHandler)
		delete transitionHandler;
	if (scrollHandler)
		delete scrollHandler;
	if (initialSpawnHandler)
		delete initialSpawnHandler;
}

void GameWorld::loadFromFile(std::string filename, Game *pGame)
{
	std::ifstream file(filename.c_str());
	std::string mapFile;
	int textureID;

	// Read in the number of backgrounds
	file >> nBkgds;

	// Allocate space for the background array
	backgrounds = new Background[nBkgds];

	for (int i = 0; i < nBkgds; i++)
	{
		// Read in the textureID and set the texture
		file >> textureID;
		backgrounds[i].setTexture(pGame->getTexture(textureID));
		backgrounds[i].init();
		backgrounds[i].setScrollRatio(0.4f);
	}

	//Read in the number of tile maps
	file >> nMaps;

	// Allocate space for map section array
	maps = new MapSection[nMaps];

	// Load tile maps
	for (int i = 0; i < nMaps; i++)
	{
		// Read in tile map filename
		file >> mapFile;
		// Read in the texture ID
		file >> textureID;
		// Read in the background ID
		file >> maps[i].bkgdID;
		// Read int the background scale type
		file >> maps[i].bkgdScale;

		maps[i].map.setTexture(pGame->getTexture(textureID));
		// Load in the map from file
		maps[i].map.loadFromFile(mapFile);
	}

	// Read in the number of transition entries
	file >> nTransitions;

	// Allocate space for transition table
	transitions = new Transition[nTransitions];

	// Fill in the entries of the transition table
	for (int i = 0; i < nTransitions; i++)
	{
		file >> transitions[i].tileMapID;
		file >> transitions[i].entryTile.x;
		file >> transitions[i].entryTile.y;
		file >> transitions[i].referenceTile.x;
		file >> transitions[i].referenceTile.y;
		file >> transitions[i].reposition;
	}


	//background.setTexture(pGame->getTexture(BKGD));


	// Close the file
	file.close();
}


void GameWorld::init()
{
	activeMap = &maps[0].map;
	activeBkgd = &backgrounds[maps[0].bkgdID];
	activeBkgd->setScale(maps[0].bkgdScale);

	//background.init();
	//background.setScrollRatio(0.4f);

	eDeathHandler = new GWEnemyDeathHandler(this);
	transitionHandler = new GWTransitionHandler(this);
	scrollHandler = new GWScrollHandler(this);
	initialSpawnHandler = new GWInitialSpawnHandler(this);

	EventManager::addHandler(Event::ENEMY_DEATH, eDeathHandler);
	EventManager::addHandler(Event::DESPAWN_ENEMY, eDeathHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::INITIAL_ENEMY_SPAWN, initialSpawnHandler);



}

void GameWorld::transition(int ent)
{
	int mapID = transitions[ent].tileMapID;
	activeMap = &maps[mapID].map;
	activeBkgd = &backgrounds[maps[mapID].bkgdID];
	activeBkgd->setScale(maps[mapID].bkgdScale);

	//activeMap->setReferenceTile(transitions[ent].referenceTile);
	activeMap->enter(transitions[ent].referenceTile);

	// Set the scroll value of the background image
	sf::Vector2f setScroll;
	setScroll.x = transitions[ent].referenceTile.x * TILE_SIZE;
	setScroll.y = transitions[ent].referenceTile.y * TILE_SIZE;
	activeBkgd->setScroll(setScroll);

	// Generate a NEW_MAP event
	sf::Vector2i entry = transitions[ent].entryTile; 
	sf::Vector2f entryPos = activeMap->getTileCenter(entry.x, entry.y);
	Event::Data e;
	e.type = Event::NEW_MAP;
	e.posX = entryPos.x;
	e.posY = entryPos.y;
	e.reposition = transitions[ent].reposition;
	e.map = (void*)activeMap;
	EventManager::triggerEvent(e);
}

void GameWorld::update(float dt)
{
	activeMap->update(dt);
}

void GameWorld::scrollBackground(sf::Vector2f ds)
{
	activeBkgd->scroll(ds);
}

void GameWorld::draw(sf::RenderWindow& window)
{
	activeBkgd->draw(window);
	activeMap->draw(window);
}