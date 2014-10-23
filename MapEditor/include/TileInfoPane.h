//==========================//
// TileInfoPane.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _TILE_INFO_PANE_H_
#define _TILE_INFO_PANE_H_

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Tile.h"
#include "RadioButton.h"
#include "Button.h"
#include "TextField.h"
#include "VScrollBar.h"

class TileInfoPane
{
public:
	// Constructor
	TileInfoPane(const sf::Font& f);
	// Destructor
	~TileInfoPane();

	void getTileInfo(Tile *tile, sf::Vector2i index);


	// Methods
	void init();
	void handleInput(Input *input);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	Tile *tile;

	sf::Font font;

	Button apply;
	sf::Text tileIndex;
	RadioButton tileType;
	sf::Text hitbox;
	TextField top;
	TextField left;
	TextField width;
	TextField height;
	RadioButton scrollXBarrier;
	RadioButton scrollYBarrier;

	sf::FloatRect bounds;
	sf::RectangleShape background;
};

#endif