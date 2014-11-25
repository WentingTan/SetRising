//==========================//
// Tile.cpp                 //
// Author: Matthew Stephens //
//==========================//
#include "Tile.h"

//===========//
// Operators //
//===========//
std::istream& operator>>(std::istream& stream, Tile& tile)
{
	char c;
	// Read in and ignore opening '('
	stream >> c;

	// Read in tile number
	stream >> tile.tileNum;
	
	// Read in tile type
	int t;
	stream >> t;
	tile.type = (TileNS::Type)t;
	
	// Set the tile solidity based on tile type
	switch (tile.type)
	{
	case TileNS::FLOOR:
	case TileNS::WALL:
		tile.solid = true;
		break;
	default: // BACKGROUND, LADDER, LADDER_TOP
		tile.solid = false;
		break;
	}
	
	// Read in the hitbox values
	stream >> tile.hitbox.left;
	stream >> tile.hitbox.top;
	stream >> tile.hitbox.width;
	stream >> tile.hitbox.height;
	
	stream >> tile.exit;

	// Read in enemy to spawn
	stream >> tile.enemy;

	// Read in and ignore closing ')'
	stream >> c;
	
	return stream;
}


std::ostream& operator<<(std::ostream& stream, Tile& tile)
{
	// Output an opening (
	stream << '(';

	// Output the tile number
	stream << tile.tileNum << ' ';
	
	// Output the tile type
	stream << tile.type << ' ';
		
	// Output the hitbox values
	stream << tile.hitbox.left << ' ';
	stream << tile.hitbox.top << ' ';
	stream << tile.hitbox.width << ' ';
	stream << tile.hitbox.height << ' ';
	

	stream << tile.exit;

	stream << tile.enemy;

	// Output a closing )
	stream << ')';
	
	return stream;
}

//========================
// Constructor
//========================
Tile::Tile()
{
	setDefault();
}

void Tile::setDefault()
{
	tileNum = -1;
	type = TileNS::BACKGROUND;
	solid = false;
	exit = -1;
	enemy = E_NONE;
	hitbox.top = 0.0f;
	hitbox.left = 0.0f;
	hitbox.width = (float)TileNS::SIZE;
	hitbox.height = (float)TileNS::SIZE;
}