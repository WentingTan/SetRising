//==========================//
// TileMap.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "TileMap.h"
#include <fstream>

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



void TileMap::loadFromFile(std::string filename)
{
	std::ifstream file(filename.c_str());

	//Read in the texture filename
	file >> tInfo.textureFile;
	
	// Load and set the texture
	texture.loadFromFile(tInfo.textureFile.c_str());
	sprite.setTexture(texture);

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
	maxTiles.y = (int)((scrollY + 585.0f) / tInfo.tileSize);

	minTiles.x = (int)(scrollX / tInfo.tileSize);
	maxTiles.x = (int)((scrollX + 670.0f) / tInfo.tileSize);
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
	scrollX += x;
	scrollY += y;

	//if (scrollX < 0.0f)
	//{
		//scrollX = 0.0f;
		//atLeftEdge = true;
	//}
	//else
		//atLeftEdge = false;

	//if (scrollX > mapSize.x * 50.0f - 800.0f)
	//{
		//scrollX = mapSize.x * 50.0f - 800.0f;
		//atRightEdge = true;
	//}
	//else
		//atRightEdge = false;
}

//=========================================================================
// update(float)
// Updates the minimum and maxmum tile indices that are visible on screen.
//=========================================================================
void TileMap::update(float dt)
{
	minTiles.y = (int)(scrollY / tInfo.tileSize);
	maxTiles.y = (int)((scrollY + 585.0f) / tInfo.tileSize);

	// Calculate the minimum and maximum visible tiles in the x direction
	minTiles.x = (int)(scrollX / tInfo.tileSize);
	maxTiles.x = (int)((scrollX + 670.0f) / tInfo.tileSize);   // 800 is screen width
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
				float xPos = xi * (float)tInfo.tileSize - offsetX + 115.0f;
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
