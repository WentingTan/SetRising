//==========================//
// OutputPane.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _OUTPUT_PANE_H_
#define _OUTPUT_PANE_H_

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "TextField.h"
#include "Button.h"
#include "Tile.h"
#include "TileMap.h"

class OutputPane
{
public:
	// Constructor
	OutputPane(const sf::Font& f, TileMap *m);
	// Destructor
	~OutputPane();

	// Methods
	void init();
	void handleInput(Input *input);
	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	sf::FloatRect bounds;
	sf::RectangleShape background;
	Button gridToggle;
	Button save;
	TextField saveFile;
	sf::Font font;
	bool gridOn;
	TileMap *map;
};

#endif