//==========================//
// TileMap.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "TileMap.h"
#include <fstream>
#include <SFML/Window/Keyboard.hpp>

//=========//
// Methods //
//=========//

//=========================================
// Destructor()
// Deallocates storage for the tile array.
//=========================================
TileMap::~TileMap()
{
	if (tiles)
		delete [] tiles;
}

//=====================================================================================
// init()
// Initializes the TileMap. Loads and sets the tile texture. Allocates space for the
// tile array, and reads in data from the map file to set the properties of each tile.
//=====================================================================================
bool TileMap::init(const char *filename)
{
	scrollX = 0.0f;
	atLeftEdge = true;
	atRightEdge = false;

	// Load and set the tile texture
	texture.loadFromFile("tiles.png");
	sprite.setTexture(texture);

	// Open the map file
	std::ifstream file(filename);
	if (!file.is_open())
	{
		return false;
	}

	// Read in the map width and height
	file >> mapSize.x;
	file >> mapSize.y;

	// Allocate space for the tile array
	tiles = new Tile[mapSize.x * mapSize.y];

	for (int i = 0; i < mapSize.x * mapSize.y; i++)
	{
		// Read in the tile number
		short n;
		file >> n;
		tiles[i].setTileNum(n);
		if (n > -1)
			tiles[i].setSolid(true);
		else
			tiles[i].setSolid(false);
		tiles[i].setHitBox(sf::FloatRect(0.0f, 0.0f, 50.0f, 50.0f));
	}

	file.close();

	return true;
}

//==================================================================================
// getTileAtPosition(float,float)
// Returns the x and y indices of the tile located at the given screen coordinates.
//==================================================================================
sf::Vector2i TileMap::getTileIndex(float x, float y)
{
	int xi = (int)((scrollX + x) / TileMapNS::TILE_SIZE.x);
	int yi = (int)(y / TileMapNS::TILE_SIZE.y);
	return sf::Vector2i(xi, yi);
}

//========================================================================================
// getTileHitBox(int,int)
// Returns true if the tile at the given index is capable of collisions, false otherwise.
// If the tile can collide, its hitbox (in screen corrdinates) is stored in the FloatRect
// reference passed to the method.
//========================================================================================
bool TileMap::getTileHitBox(int x, int y, sf::FloatRect& box)
{
	Tile tile = tiles[mapSize.x * y + x];

	if (tile.isSolid())
	{
		box = tile.getHitBox();
		box.left = x * (float)TileMapNS::TILE_SIZE.x - scrollX;
		box.top = y * (float)TileMapNS::TILE_SIZE.y;
		return true;
	}

	return false;
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
// Scrolls the TileMap horizontally by the given amount. Ensures the map does not scroll
// beyond its boundaries.
//=======================================================================================
void TileMap::scroll(float x)
{
	scrollX += x;

	if (scrollX < 0.0f)
	{
		scrollX = 0.0f;
		atLeftEdge = true;
	}
	else
		atLeftEdge = false;

	if (scrollX > mapSize.x * 50.0f - 800.0f)
	{
		scrollX = mapSize.x * 50.0f - 800.0f;
		atRightEdge = true;
	}
	else
		atRightEdge = false;
}

//=========================================================================
// update(float)
// Updates the minimum and maxmum tile indices that are visible on screen.
//=========================================================================
void TileMap::update(float dt)
{
	minTiles.y = 0;
	maxTiles.y = 12;

	// Calculate the minimum and maximum visible tiles in the x direction
	minTiles.x = (int)(scrollX / TileMapNS::TILE_SIZE.x);
	maxTiles.x = (int)((scrollX + 800.0f) / TileMapNS::TILE_SIZE.x);   // 800 is screen width
}

//===================================================================================
// draw(sf::RenderWindow&)
// Iterates through the tile array from the minimum to maximum visible index in each
// direction, and draws each tile to the screen by setting the tile texture rect
// according to the tile number, and calculating its screen position.
//===================================================================================
void TileMap::draw(sf::RenderWindow& backBuffer)
{

	float offset = scrollX - minTiles.x * (float)TileMapNS::TILE_SIZE.x;

	for (int y = minTiles.y, yi = 0; y < maxTiles.y + 1; y++, yi++)
	{
		for (int x = minTiles.x, xi = 0; x < maxTiles.x + 1; x++, xi++)
		{
			// Calculate array index using row major order
			int tn = tiles[mapSize.x * y + x].getTileNum();
			if (tn >= 0)
			{
				// Calculate texture rect for current tile
				int row = tn / TileMapNS::TPR;
				int col = tn % TileMapNS::TPR;
				sf::IntRect rect;
				rect.top = row * TileMapNS::TILE_SIZE.y;
				rect.left = col * TileMapNS::TILE_SIZE.x;
				rect.width = TileMapNS::TILE_SIZE.x;
				rect.height = TileMapNS::TILE_SIZE.y;

				// Set the sprite texture rect
				sprite.setTextureRect(rect);

				// Calculate its position in screen coordinates
				float xPos = xi * (float)TileMapNS::TILE_SIZE.x - offset;
				float yPos = yi * (float)TileMapNS::TILE_SIZE.y;
				sprite.setPosition(xPos, yPos);

				// Draw the sprite to the screen
				backBuffer.draw(sprite);
			}
		}
	}
}

