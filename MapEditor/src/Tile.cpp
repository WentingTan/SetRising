//==========================//
// Tile.cpp                 //
// Author: Matthew Stephens //
//==========================//
#include "Tile.h"

bool TileNS::Solid[TileNS::NUM_TYPES] = {
	false,
	true,
	true,
	false,
	false
};

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
	tile.solid = TileNS::Solid[t];
	
	// Read in the hitbox values
	stream >> tile.hitbox.left;
	stream >> tile.hitbox.top;
	stream >> tile.hitbox.width;
	stream >> tile.hitbox.height;
	
	stream >> c;
	tile.scrollXBarrier = c == 'y' ? true : false;

	stream >> c;
	tile.scrollYBarrier = c == 'y' ? true : false;

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
	
	stream << (tile.scrollXBarrier ? 'y' : 'n') << ' ';
	
	stream << (tile.scrollYBarrier ? 'y' : 'n') << ' ';

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
	scrollXBarrier = false;
	scrollYBarrier = false;
	enemy = E_NONE;
	hitbox.top = 0.0f;
	hitbox.left = 0.0f;
	hitbox.width = (float)TileNS::SIZE;
	hitbox.height = (float)TileNS::SIZE;
}