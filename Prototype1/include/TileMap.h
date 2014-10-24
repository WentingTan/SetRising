//==========================//
// TileMap.h                //
// Author: Matthew Stephens //
//==========================//
#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <string>
#include <fstream>

namespace TileMapNS
{
	// Tiles per row in the texture
	const int TPR = 5;
	const sf::Vector2i TILE_SIZE = sf::Vector2i(50, 50);
}

typedef struct sTileMapInfo
{
	std::string textureFile;
	int nTiles;
	int tileSize;
	int tpr;
	sf::Vector2i mapSize;
} TileMapInfo;

class TileMap
{
public:
	// Constructor
	TileMap();
	// Destructor
	~TileMap();

	bool isAtLeftEdge();
	bool isAtRightEdge();

	// Methods
	void loadFromFile(std::string filename);
	void create(sf::Texture *pTexture, TileMapInfo info);
	void setTexture(sf::Texture *t);

	Tile* getTileByPos(float x, float y);
	Tile* getTileByIndex(int x, int y);

	TileMapInfo getTileMapInfo();

	void save(std::string filename);

	sf::Vector2i getTileIndex(float x, float y);
	bool isTileObstactle(int x, int y);
	sf::FloatRect getTileHitBox(int x, int y);
	TileNS::Type getTileType(int x, int y);
	short getTileNum(int x, int y);

	void scroll(float x, float y);

	void update(float dt);
	void draw(sf::RenderWindow& backBuffer);

private:
	sf::Sprite sprite;
	sf::Texture *texture;
	//sf::Vector2i mapSize;
	sf::Vector2i minTiles;
	sf::Vector2i maxTiles;
	Tile *tiles;
	float scrollX;
	float scrollY;
	bool atLeftEdge;
	bool atRightEdge;
	TileMapInfo tInfo;

};

#endif