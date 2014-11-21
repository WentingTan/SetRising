//==========================//
// NewMenu.h                //
// Author: Matthew Stephens //
//==========================//
#ifndef _NEW_MENU_H_
#define _NEW_MENU_H_

#include "AppState.h"
#include "Button.h"
#include "TextField.h"
#include "MapEditor.h"

class NewMenu : public AppState
{
public:
	// Constructor
	NewMenu(const sf::Font& f, MapEditor *m);

	// Methods
	virtual void init();
	virtual void handleInput(Input *input);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

private:
	sf::Text title;
	Button ok;

	TextField tileTexture;
	TextField nTiles;
	TextField tileSize;
	TextField tilesPerRow;
	TextField mapX;
	TextField mapY;
};

#endif