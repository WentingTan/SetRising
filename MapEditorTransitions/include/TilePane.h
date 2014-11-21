//==========================//
// TilePane.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _TILE_PANE_H_
#define _TILE_PANE_H_

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "VScrollBar.h"

class TilePane
{
public:
	// Constructor
	TilePane(sf::Texture *texture, int nTiles, int tileSize);
	// Destructor
	~TilePane();

	int getSelected() const;

	// Methods
	void init(int tpr);
	void handleInput(Input *input);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	sf::FloatRect bounds;
	sf::Texture *texture;
	sf::RectangleShape background;
	sf::RectangleShape select;
	//sf::RectangleShape highlight;
	sf::Sprite *tiles;
	VScrollBar *vscroll;
	int tileSize;


	sf::Texture tools;
	sf::Sprite eraser;
	sf::Sprite pointer;


	int nTiles;
	int selected;
	//int mouseOver;

	// Helpers
	void scroll(float y);
};

#endif