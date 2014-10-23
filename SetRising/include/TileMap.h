//==========================//
// TileMap.h                //
// Author: Matthew Stephens //
//==========================//
#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_

#include <SFML/Graphics.hpp>
#include "Tile.h"

namespace TileMapNS
{
	// Tiles per row in the texture
	const int TPR = 3;
	const sf::Vector2i TILE_SIZE = sf::Vector2i(50, 50);
}

class TileMap
{
public:
	// Constructor
	TileMap() {}
	// Destructor
	~TileMap();

	bool isAtLeftEdge();
	bool isAtRightEdge();

	// Methods
	bool init(const char *filename);

	sf::Vector2i getTileIndex(float x, float y);
	bool getTileHitBox(int x, int y, sf::FloatRect& box);

	void scroll(float x);

	void update(float dt);
	void draw(sf::RenderWindow& backBuffer);

private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2i mapSize;
	sf::Vector2i minTiles;
	sf::Vector2i maxTiles;
	Tile *tiles;
	float scrollX;
	bool atLeftEdge;
	bool atRightEdge;

};

#endif