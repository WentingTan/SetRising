//==========================//
// Tile.cpp                 //
// Author: Matthew Stephens //
//==========================//
#include "Tile.h"

//===========//
// Accessors //
//===========//

//=================================
// getHitBox()
// Returns the hitbox of the tile.
//=================================
sf::FloatRect Tile::getHitBox() const
{
	return hitbox;
}

//=================================================================
// isSolid()
// Returns true if the tile may be collided with, false otherwise.
//=================================================================
bool Tile::isSolid() const
{
	return solid;
}

//===================================================================
// getTileNum()
// Returns the tile number (i.e. which graphic is used) of the tile.
//===================================================================
short Tile::getTileNum() const
{
	return tileNum;
}


//===========//
// Mutators  //
//===========//

//==========================
// setHitBox(sf::FloatRect)
// Sets the tile's hitbox.
//==========================
void Tile::setHitBox(sf::FloatRect box)
{
	hitbox = box;
}

//====================================================
// setSolid(bool)
// Sets whether or not the tile can be collided with.
//====================================================
void Tile::setSolid(bool sol)
{
	solid = sol;
}

//================================================================
// setTileNum(short)
// Sets the tile number (i.e. which graphic is used) of the tile.
//================================================================
void Tile::setTileNum(short num)
{
	tileNum = num;
}
