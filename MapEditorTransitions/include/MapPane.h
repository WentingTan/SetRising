//==========================//
// MapPane.h                //
// Author: Matthew Stephens //
//==========================//
#ifndef _MAP_PANE_H_
#define _MAP_PANE_H_

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Tile.h"
#include "VScrollBar.h"
#include "HScrollBar.h"
#include "TileMap.h"

class MapPane
{
public:
	// Constructor
	MapPane(TileMap *pMap);
	// Destructor
	~MapPane();

	void setSelectedGraphic(int sel);

	bool newSelected();

	Tile* getSelectedTile(int& x, int& y);


	// Methods
	void init();
	void handleInput(Input *input);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	sf::FloatRect bounds;

	Tile *tile;
	sf::Vector2i index;

	VScrollBar *vscroll;
	HScrollBar *hscroll;
	sf::RectangleShape highlight;

	TileMap *map;
	bool newSel;
	int selected;

};

#endif