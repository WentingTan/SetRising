//==========================//
// Tile.h                   //
// Author: Matthew Stephens //
//==========================//
#ifndef _TILE_H_
#define _TILE_H_

#include <SFML/Graphics.hpp>
#include <fstream>

namespace TileNS
{
	const int SIZE = 50;

	enum Type
	{
		BACKGROUND = 0,
		FLOOR = 1,
		WALL = 2,
		LADDER = 3,
		LADDER_TOP = 4,
		NUM_TYPES = 5
	};

	bool Solid[];
}

class Tile
{
public:
	// Constructor
	Tile();

	void setDefault();

	sf::FloatRect hitbox;
	bool solid;
	bool scrollXBarrier;
	bool scrollYBarrier;
	TileNS::Type type;
	short tileNum;
};

// Stream operators
std::istream& operator>>(std::istream& stream, Tile& tile);
std::ostream& operator<<(std::ostream& stream, Tile& tile);

#endif