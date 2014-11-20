//==========================//
// TileMap.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "TileMap.h"
#include <fstream>
#include "EventManager.h"
#include "Constants.h"

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

	// Use map size to determine max scroll values
	minScroll.x = (float)TileNS::SIZE;
	minScroll.y = (float)TileNS::SIZE;
	maxScroll.x = (float)(tInfo.mapSize.x - 1) * (float)TileNS::SIZE - SCREEN_WIDTH;
	maxScroll.y = (float)(tInfo.mapSize.y - 1) * (float)TileNS::SIZE - SCREEN_HEIGHT;

	// Allocate space for the map
	tiles = new Tile[tInfo.mapSize.x * tInfo.mapSize.y];

	// Read in the tiles
	for (int i = 0; i < tInfo.mapSize.x * tInfo.mapSize.y; i++)
		file >> tiles[i];

	file.close();


	scrollX = minScroll.x;
	scrollY = minScroll.y;

	checkBoundaries();


	// Calculate the minimum and maximum visible tiles
	minTiles.y = (int)(scrollY / tInfo.tileSize);
	maxTiles.y = (int)((scrollY + SCREEN_HEIGHT) / tInfo.tileSize);

	minTiles.x = (int)(scrollX / tInfo.tileSize);
	maxTiles.x = (int)((scrollX + SCREEN_WIDTH) / tInfo.tileSize);
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


//=====================================================================
// TileMap::indexIsWithinBounds(int,int)
// Determines if the given index is within the bounds of the tile map.
//=====================================================================
bool TileMap::indexIsWithinBounds(int x, int y)
{
	if (x > -1 && y > -1 && x < tInfo.mapSize.x && y < tInfo.mapSize.y)
		return true;
	else
		return false;
}

//=======================================================================================
// TileMap::enter(sf::Vector2i, sf::Vector2i)
// This method is called when entering a new tile map. The reference tile is the tile
// that should appear at the top right corner of the screen upon entering. The reference
// tile is used to compute x and y scroll values, which in turn are used to compute the
// minimum and maximum visible tiles.
//=======================================================================================
void TileMap::enter(sf::Vector2i ref)
{
	// Set the scroll values based on reference tile
	scrollX = (float)ref.x * (float)TileNS::SIZE;
	scrollY = (float)ref.y * (float)TileNS::SIZE;

	checkBoundaries();

	// Calculate the minimum and maximum visible tiles
	minTiles.y = (int)(scrollY / tInfo.tileSize);
	maxTiles.y = (int)((scrollY + SCREEN_HEIGHT) / tInfo.tileSize);

	minTiles.x = (int)(scrollX / tInfo.tileSize);
	maxTiles.x = (int)((scrollX + SCREEN_WIDTH) / tInfo.tileSize);
}

//================================================================================
// TileMap::initialSpawn()
// Does an initial sweep of the visible tiles and spawns enemies where indicated.
// This method is called from an event handler for Event::INITIAL_ENEMY_SPAWN.
//================================================================================
void TileMap::initialSpawn()
{
	for (int y = minTiles.y - 1; y < maxTiles.y + 2; y++)
		for (int x = minTiles.x - 1; x < maxTiles.x + 2; x++)
			if (indexIsWithinBounds(x, y))
				if (tiles[tInfo.mapSize.x * y + x].enemy != E_NONE)
					spawnEnemy(sf::Vector2i(x, y));
}


//==================================================================================
// getTileAtPosition(float,float)
// Returns the x and y indices of the tile located at the given screen coordinates.
//==================================================================================
sf::Vector2i TileMap::getTileIndex(float x, float y)
{
	int xi = (int)((scrollX + x) / tInfo.tileSize);
	if (xi < 0)
		xi = 0;
	else if (xi > tInfo.mapSize.x)
		xi = tInfo.mapSize.x;

	int yi = (int)((scrollY + y) / tInfo.tileSize);
	if (yi < 0)
		yi = 0;
	else if (yi > tInfo.mapSize.y)
		yi = tInfo.mapSize.y;

	return sf::Vector2i(xi, yi);
}


Tile* TileMap::getTileByPos(float x, float y)
{
	sf::Vector2i ind = getTileIndex(x, y);
	return getTileByIndex(ind.x, ind.y);
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
	box.left += x * (float)tInfo.tileSize - scrollX;
	box.top += y * (float)tInfo.tileSize - scrollY;
	
	return box;
}


sf::Vector2f TileMap::getTileCenter(int x, int y)
{
	sf::Vector2f pos;
	pos.x = ((float)x + 0.5f) * (float)TileNS::SIZE - scrollX;
	pos.y = ((float)y + 0.5f) * (float)TileNS::SIZE - scrollY;
	return pos;
}

bool TileMap::isAtBoundary(int edge)
{
	switch (edge)
	{
	case LEFT_EDGE:
		return atLeftEdge;
		break;
	case RIGHT_EDGE:
		return atRightEdge;
		break;
	case TOP_EDGE:
		return atTopEdge;
		break;
	case BOTTOM_EDGE:
		return atBottomEdge;
		break;
	default:
		return false;
		break;
	}
}

//====================================================================================
// scroll(float)
// Scrolls the TileMap by adding the given values to the map's x and y scroll values.
// Checks to see if the map has scrolled to any of its edges, and triggers a scroll
// event with the amounts by which the map scrolled.
//====================================================================================
void TileMap::scroll(float x, float y)
{
	scrollX += x;
	scrollY += y;

	checkBoundaries();

	Event::Data e;
	e.type = Event::SCROLL;
	e.scrollX = x;
	e.scrollY = y;
	EventManager::triggerEvent(e);
}


void TileMap::resetEnemySpawnPoint(sf::Vector2i tile, int type)
{
	tiles[tInfo.mapSize.x * tile.y + tile.x].enemy = type;
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

	newMax.x = (int)((scrollX + SCREEN_WIDTH) / tInfo.tileSize);
	newMax.y = (int)((scrollY + SCREEN_HEIGHT) / tInfo.tileSize);

	// Scan for enemies to spawn based on the direction of scrolling in the current frame
	if (newMax.x > maxTiles.x && newMax.x + 1 < tInfo.mapSize.x)
	{
		for (int y = newMin.y; y < newMax.y; y++)
			if (tiles[tInfo.mapSize.x * y + newMax.x + 1].enemy != E_NONE)
				spawnEnemy(sf::Vector2i(newMax.x + 1, y));	
	}
	else if (newMin.x < minTiles.x && newMin.x > 0)
	{
		for (int y = newMin.y; y < newMax.y; y++)
			if (tiles[tInfo.mapSize.x * y + newMin.x - 1].enemy != E_NONE)
				spawnEnemy(sf::Vector2i(newMin.x - 1, y));
				
	}

	if (newMax.y > maxTiles.y && newMax.y + 1 < tInfo.mapSize.y)
	{
		for (int x = newMin.x; x < newMax.x; x++)
			if (tiles[tInfo.mapSize.x * (newMax.y + 1) + x].enemy != E_NONE)
				spawnEnemy(sf::Vector2i(x, newMax.y + 1));	
	}
	else if (newMin.y < minTiles.y && newMin.y > 0)
	{
		for (int x = newMin.x; x < newMax.x; x++)
			if (tiles[tInfo.mapSize.x * (newMin.y - 1) + x].enemy != E_NONE)
				spawnEnemy(sf::Vector2i(x, newMin.y - 1));
				
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
void TileMap::spawnEnemy(sf::Vector2i tile)
{
	// Calculate the position of the tile in screen corrdinates
	sf::Vector2f pos;
	// Use the center of the tile in the x direction
	pos.x = ((float)tile.x + 0.5f) * (float)tInfo.tileSize - scrollX;
	// Use the top of the tile in the y direction
	pos.y = (float)tile.y * (float)tInfo.tileSize - scrollY;
	
	// Generate a SPAWN_ENEMY event
	Event::Data e;
	e.type = Event::SPAWN_ENEMY;
	e.enemyType = tiles[tInfo.mapSize.x * tile.y + tile.x].enemy;
	e.posX = pos.x;
	e.posY = pos.y;
	e.tile = tile;
	EventManager::triggerEvent(e);

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
	//sf::RectangleShape hb;
	//hb.setFillColor(sf::Color(0, 0, 255, 175));

	//sprite.setColor(sf::Color(255,155,155));

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


				//sf::FloatRect hbox = getTileHitBox(x, y);
				//hb.setPosition(hbox.left, hbox.top);
				//hb.setSize(sf::Vector2f(hbox.width, hbox.height));
				//backBuffer.draw(hb);

			}
		}
	}
}




short TileMap::getTileNum(int x, int y)
{
	return tiles[tInfo.mapSize.x * y + x].tileNum;
}

//======================================================================================
// TileMap::checkBoundaries()
// Based on the x and y scroll values, determines if the TileMap has scrolled to any of
// its edges.  Sets a boolean value for each edge.
//======================================================================================
void TileMap::checkBoundaries()
{
	// Determine if at left boundary
	if (scrollX <= minScroll.x)
	{
		scrollX = minScroll.x;
		atLeftEdge = true;
	}
	else
		atLeftEdge = false;

	// Determine if at right boundary
	if (scrollX >= maxScroll.x)
	{
		scrollX = maxScroll.x;
		atRightEdge = true;
	}
	else
		atRightEdge = false;

	// Determine if at top boundary
	if (scrollY <= minScroll.y)
	{
		scrollY = minScroll.y;
		atTopEdge = true;
	}
	else
		atTopEdge = false;

	// Determine if at bottom boundary
	if (scrollY >= maxScroll.y)
	{
		scrollY = maxScroll.y;
		atBottomEdge = true;
	}
	else
		atBottomEdge = false;
}