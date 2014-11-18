//==========================//
// GameWorld.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "GameWorld.h"
#include "Game.h"
#include <fstream>
#include "EventManager.h"


void GWEnemyDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_DEATH || e.type == Event::DESPAWN_ENEMY)
		pGW->getActiveMap()->resetEnemySpawnPoint(e.tile);
}


void GWTransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION)
		pGW->transition(e.entrance);
}

TileMap* GameWorld::getActiveMap()
{
	return activeMap;
}

void GameWorld::loadFromFile(std::string filename, Game *pGame)
{
	std::ifstream file(filename.c_str());
	std::string mapFile;
	int textureID;

	//Read in the number of tile maps
	file >> nMaps;

	// Allocate space for tile map array
	maps = new TileMap[nMaps];

	// Load tile maps
	for (int i = 0; i < nMaps; i++)
	{
		// Read in tile map filename
		file >> mapFile;
		// Read in the texture ID
		file >> textureID;

		maps[i].setTexture(pGame->getTexture(textureID));
		// Load in the map from file
		maps[i].loadFromFile(mapFile);
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

	// Close the file
	file.close();
}


void GameWorld::init()
{
	activeMap = &maps[0];

	eDeathHandler = new GWEnemyDeathHandler(this);
	transitionHandler = new GWTransitionHandler(this);

	EventManager::addHandler(Event::ENEMY_DEATH, eDeathHandler);
	EventManager::addHandler(Event::DESPAWN_ENEMY, eDeathHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
}

void GameWorld::transition(int ent)
{
	int mapID = transitions[ent].tileMapID;
	activeMap = &maps[mapID];

	//activeMap->setReferenceTile(transitions[ent].referenceTile);
	activeMap->enter(transitions[ent].referenceTile);

	// Generate an event to notify player of new position
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

void GameWorld::draw(sf::RenderWindow& window)
{
	activeMap->draw(window);
}