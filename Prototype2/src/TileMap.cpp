//==========================//
// TileMap.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "TileMap.h"
#include <fstream>
#include "EventManager.h"




void TMEnemyDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_DEATH)
		pTM->resetEnemySpawnPoint(e.tile);
}





//=========//
// Methods //
//=========//

TileMap::TileMap()
{

}

//=========================================
// Destructor()
// Deallocates storage for the tile array.
//=========================================
TileMap::~TileMap()
{
	if (tiles)
		delete [] tiles;
}

void TileMap::setTexture(sf::Texture *t)
{
	texture = t;
}

void TileMap::loadFromFile(std::string filename)
{
	std::ifstream file(filename.c_str());

	//Read in the texture filename
	file >> tInfo.textureFile;
	
	// Set the texture
	sprite.setTexture(*texture);

	// Read in the number of tiles in the texture
	file >> tInfo.nTiles;

	// Read in the tile size
	file >> tInfo.tileSize;

	// Read in the tiles per row in the texture
	file >> tInfo.tpr;

	// Read in the map size
	file >> tInfo.mapSize.x;
	file >> tInfo.mapSize.y;

	// Allocate space for the map
	tiles = new Tile[tInfo.mapSize.x * tInfo.mapSize.y];

	// Read in the tiles
	for (int i = 0; i < tInfo.mapSize.x * tInfo.mapSize.y; i++)
		file >> tiles[i];

	file.close();


	scrollY = scrollX = 0;

	// Calculate the minimum and maximum visible tiles
	minTiles.y = (int)(scrollY / tInfo.tileSize);
	maxTiles.y = (int)((scrollY + 600.0f) / tInfo.tileSize);

	minTiles.x = (int)(scrollX / tInfo.tileSize);
	maxTiles.x = (int)((scrollX + 800.0f) / tInfo.tileSize);
}

void TileMap::create(sf::Texture *t, TileMapInfo i)
{
	tInfo = i;

	// Set the texture
	sprite.setTexture(*t);

	// Allocate space for the map
	tiles = new Tile[tInfo.mapSize.x * tInfo.mapSize.y];

	scrollY = scrollX = 0;

	// Calculate the minimum and maximum visible tiles
	minTiles.y = (int)(scrollY / tInfo.tileSize);
	maxTiles.y = (int)((scrollY + 585.0f) / tInfo.tileSize);

	minTiles.x = (int)(scrollX / tInfo.tileSize);
	maxTiles.x = (int)((scrollX + 670.0f) / tInfo.tileSize);   // 800 is screen width
}


void TileMap::save(std::string filename)
{
	std::ofstream file(filename.c_str());

	// Write the name of the texture file used
	file << tInfo.textureFile << ' ';

	// Write the number of tiles in the texture
	file << tInfo.nTiles << ' ';

	// Write the tile size
	file << tInfo.tileSize << ' ';

	// Write the tiles per row in the texture
	file << tInfo.tpr << ' ';

	// Write the map size
	file << tInfo.mapSize.x << ' ' << tInfo.mapSize.y << std::endl;

	// Write the tiles
	for (int i = 0; i < tInfo.mapSize.x * tInfo.mapSize.y; i++)
		file << tiles[i] << std::endl;

	file.close();
}


//==================================================================================
// getTileAtPosition(float,float)
// Returns the x and y indices of the tile located at the given screen coordinates.
//==================================================================================
sf::Vector2i TileMap::getTileIndex(float x, float y)
{
	int xi = (int)((scrollX + x) / tInfo.tileSize);
	int yi = (int)((scrollY + y) / tInfo.tileSize);
	return sf::Vector2i(xi, yi);
}



TileMapInfo TileMap::getTileMapInfo()
{
	return tInfo;
}


Tile* TileMap::getTileByIndex(int x, int y)
{
	if (x >= tInfo.mapSize.x || y >= tInfo.mapSize.y)
		return NULL;
	return &tiles[tInfo.mapSize.x * y + x];
}


//==============================================
// isTileObstacle(int,int)
//==============================================
bool TileMap::isTileObstactle(int x, int y)
{
	Tile tile = tiles[tInfo.mapSize.x * y + x];
	return tile.solid;
}

//==============================================
// getTileType(int,int)
//==============================================
TileNS::Type TileMap::getTileType(int x, int y)
{
	Tile tile = tiles[tInfo.mapSize.x * y + x];
	return tile.type;
}

//========================================================================================
// getTileHitBox(int,int)
// 
//========================================================================================
sf::FloatRect TileMap::getTileHitBox(int x, int y)
{
	Tile tile = tiles[tInfo.mapSize.x * y + x];

	sf::FloatRect box = tile.hitbox;
	box.left = x * (float)tInfo.tileSize - scrollX;
	box.top = y * (float)tInfo.tileSize - scrollY;
	
	return box;
}

//===================================================================================
// isAtLeftEdge()
// Returns true if the TileMap is scrolled all the way to the left, false otherwise.
//===================================================================================
bool TileMap::isAtLeftEdge()
{
	return atLeftEdge;
}

//====================================================================================
// isAtRightEdge()
// Returns true if the TileMap is scrolled all the way to the right, false otherwise.
//====================================================================================
bool TileMap::isAtRightEdge()
{
	return atRightEdge;
}

//=======================================================================================
// scroll(float)
// 
//=======================================================================================
void TileMap::scroll(float x, float y)
{
	ds.x = x;
	ds.y = y;
	scrollX += x;
	scrollY += y;

	//enemies->scroll(ds);
	Event::Data e;
	e.type = Event::SCROLL;
	e.scrollX = ds.x;
	e.scrollY = ds.y;
	EventManager::triggerEvent(e);

	if (scrollX < 0.0f)
	{
		scrollX = 0.0f;
		atLeftEdge = true;
	}
	else
		atLeftEdge = false;

	if (scrollX > tInfo.mapSize.x * 50.0f - 800.0f)
	{
		scrollX = tInfo.mapSize.x * 50.0f - 800.0f;
		atRightEdge = true;
	}
	else
		atRightEdge = false;
}


void TileMap::init()
{
	eDeathHandler = new TMEnemyDeathHandler(this);
	EventManager::addHandler(Event::ENEMY_DEATH, eDeathHandler);
}

void TileMap::resetEnemySpawnPoint(sf::Vector2i tile)
{
	tiles[tInfo.mapSize.x * tile.y + tile.x].enemy = E_SOLDIER;
}



//=========================================================================================
// TileMap::update(float)
// Updates the minimum and maxmum tile indices that are visible on screen. If these values
// have changed since the last frame, then the perimeter tiles just offscreen are scanned.
// If one of the perimeter tiles is a spawn point for the enemy, a SPAWN_ENEMY event is
// generated.
//=========================================================================================
void TileMap::update(float dt)
{
	// Calculate the new minimum and maximum visible tiles
	sf::Vector2i newMin;
	sf::Vector2i newMax;

	newMin.x = (int)(scrollX / tInfo.tileSize);
	newMin.y = (int)(scrollY / tInfo.tileSize);

	newMax.x = (int)((scrollX + 800.0f) / tInfo.tileSize);
	newMax.y = (int)((scrollY + 600.0f) / tInfo.tileSize);

	//MODIFYING
	//
	//

	// Scan for enemies to spawn based on the direction of scrolling in the current frame
	if (newMax.x > maxTiles.x && newMax.x + 1 < tInfo.mapSize.x)
	{
		for (int y = newMin.y; y < newMax.y; y++)
			if (tiles[tInfo.mapSize.x * y + newMax.x + 1].enemy == E_SOLDIER)
				spawnEnemy(sf::Vector2i(newMax.x + 1, y), -1.0f);
			else if (tiles[tInfo.mapSize.x * y + newMax.x + 1].enemy == E_BOSS)
				spawnBoss(sf::Vector2i(newMax.x + 1, y), -1.0f);
			
	}
	else if (newMin.x < minTiles.x && newMin.x > 0)
	{
		for (int y = newMin.y; y < newMax.y; y++)
			if (tiles[tInfo.mapSize.x * y + newMin.x - 1].enemy == E_SOLDIER)
				spawnEnemy(sf::Vector2i(newMin.x - 1, y), 1.0f);
			else if (tiles[tInfo.mapSize.x * y + newMax.x - 1].enemy == E_BOSS)
				spawnBoss(sf::Vector2i(newMax.x - 1, y), -1.0f);
				
	}

	// Update the minimum and maximum visible tiles
	minTiles = newMin;
	maxTiles = newMax;
}

//================================================================================
// TileMap::spawnEnemy(sf::Vector2i)
// Helper method that calculates the screen coordinates of the given tile and
// generates a SPAWN_ENEMY event. After the event is generated, the spawn enemy
// flag is removed from the tile, so that enemies don't continually spawn if the
// player were to walk back and forth causing the tile to alternate between on
// screen and off screen. The spawn enemy flag is reset when the enemy is killed.
//================================================================================
void TileMap::spawnEnemy(sf::Vector2i tile, float dir)
{
	// Calculate the position of the tile in screen corrdinates
	sf::Vector2f pos;
	// Use the center of the tile in the x direction
	pos.x = ((float)tile.x + 0.5f) * (float)tInfo.tileSize - scrollX;
	// Use the top of the tile in the y direction
	pos.y = (float)tile.y * (float)tInfo.tileSize - scrollY;
	

	// Trigger a SPAWN_ENEMY event
	Event::Data e;
	e.type = Event::SPAWN_ENEMY;
	e.posX = pos.x;
	e.posY = pos.y;
	e.tile = tile;
	e.dir = dir;
	EventManager::triggerEvent(e);

	/*
	boss.setTexture(pGame->getTexture(BOSS));
	boss.init();
	boss.setTileMap(&tmap);
	
	*/




	// Ensure the tile doesn't continue spawning enemies
	tiles[tInfo.mapSize.x * tile.y + tile.x].enemy = E_NONE;
}

void TileMap::spawnBoss(sf::Vector2i tile, float dir)
{
	// Calculate the position of the tile in screen corrdinates
	sf::Vector2f pos;
	// Use the center of the tile in the x direction
	pos.x = ((float)tile.x + 0.5f) * (float)tInfo.tileSize - scrollX;
	// Use the top of the tile in the y direction
	pos.y = (float)tile.y * (float)tInfo.tileSize - scrollY;


	// Trigger a SPAWN_ENEMY event
	Event::Data e;
	e.type = Event::SPAWN_BOSS;
	e.posX = pos.x;
	e.posY = pos.y;
	e.tile = tile;
	e.dir = dir;
	EventManager::triggerEvent(e);

	/*
	boss.setTexture(pGame->getTexture(BOSS));
	boss.init();
	boss.setTileMap(&tmap);

	*/




	// Ensure the tile doesn't continue spawning enemies
	tiles[tInfo.mapSize.x * tile.y + tile.x].enemy = E_NONE;
}


//===================================================================================
// draw(sf::RenderWindow&)
// Iterates through the tile array from the minimum to maximum visible index in each
// direction, and draws each tile to the screen by setting the tile texture rect
// according to the tile number, and calculating its screen position.
//===================================================================================
void TileMap::draw(sf::RenderWindow& backBuffer)
{

	float offsetX = scrollX - minTiles.x * (float)tInfo.tileSize;
	float offsetY = scrollY - minTiles.y * (float)tInfo.tileSize;

	for (int y = minTiles.y, yi = 0; y < maxTiles.y + 1; y++, yi++)
	{
		for (int x = minTiles.x, xi = 0; x < maxTiles.x + 1; x++, xi++)
		{
			// Calculate array index using row major order
			int ind = tInfo.mapSize.x * y + x;
			if (ind > tInfo.mapSize.x * tInfo.mapSize.y || ind < 0)
				continue;
			int tn = (int)tiles[ind].tileNum;
			if (tn >= 0)
			{
				// Calculate texture rect for current tile
				int row = tn / tInfo.tpr;
				int col = tn % tInfo.tpr;
				sf::IntRect rect;
				rect.top = row * tInfo.tileSize;
				rect.left = col * tInfo.tileSize;
				rect.width = tInfo.tileSize;
				rect.height = tInfo.tileSize;

				// Set the sprite texture rect
				sprite.setTextureRect(rect);

				// Calculate its position in screen coordinates
				float xPos = xi * (float)tInfo.tileSize - offsetX;
				float yPos = yi * (float)tInfo.tileSize - offsetY;
				sprite.setPosition(xPos, yPos);

				// Draw the sprite to the screen
				backBuffer.draw(sprite);
			}
		}
	}
}




short TileMap::getTileNum(int x, int y)
{
	return tiles[tInfo.mapSize.x * y + x].tileNum;
}
