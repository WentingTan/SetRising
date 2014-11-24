//==========================//
// TileMap.h                //
// Author: Matthew Stephens //
//==========================//
#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "EnemyManager.h"
#include <string>
#include <fstream>
#include "EventHandler.h"

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

	bool isAtBoundary(int edge);

	void init();
	void enter(sf::Vector2i ref);
	void resetSpawnPoint(sf::Vector2i tile, int type);

	void setReferenceTile(sf::Vector2i ref);
	void initialSpawn();
	bool indexIsWithinBounds(int x, int y);

	void loadFromFile(std::string filename);
	void create(sf::Texture *pTexture, TileMapInfo info);
	void setTexture(sf::Texture *t);

	Tile* getTileByPos(float x, float y);
	Tile* getTileByIndex(int x, int y);

	sf::Vector2f getTileCenter(int x, int y);

	sf::Vector2i getTileIndex(float x, float y);
	bool isTileObstacle(int x, int y);
	sf::FloatRect getTileHitBox(int x, int y);
	TileNS::Type getTileType(int x, int y);
	short getTileNum(int x, int y);

	void scroll(float x, float y);

	void update(float dt);
	void draw(sf::RenderWindow& backBuffer);

private:
	sf::Sprite sprite;
	sf::Texture *texture;
	sf::Vector2i minTiles;
	sf::Vector2i maxTiles;
	sf::Vector2f minScroll;
	sf::Vector2f maxScroll;
	Tile *tiles;
	float scrollX;
	float scrollY;
	bool atLeftEdge;
	bool atRightEdge;
	bool atTopEdge;
	bool atBottomEdge;
	TileMapInfo tInfo;
	sf::Vector2f ds;
	//EnemyManager *enemies;

	// Helpers
	void spawn(sf::Vector2i tile);
	void spawnEnemy(sf::Vector2i tile);
	void spawnWeapon(sf::Vector2i tile);
	void spawnIceblock(sf::Vector2i tile);
	void checkBoundaries();
};

#endif