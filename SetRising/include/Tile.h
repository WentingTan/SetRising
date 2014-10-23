//==========================//
// Tile.h                   //
// Author: Matthew Stephens //
//==========================//
#ifndef _TILE_H_
#define _TILE_H_

#include <SFML/Graphics.hpp>

class Tile
{
public:
	// Constructor
	Tile() {}

	// Accessors
	sf::FloatRect getHitBox() const;
	bool isSolid() const;
	short getTileNum() const;

	// Mutators
	void setHitBox(sf::FloatRect box);
	void setSolid(bool sol);
	void setTileNum(short num);

private:
	sf::FloatRect hitbox;
	bool solid;
	short tileNum;
};

#endif