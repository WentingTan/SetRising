//==========================//
// EditState.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _EDIT_STATE_H_
#define _EDIT_STATE_H_

#include "AppState.h"
#include "Button.h"
#include "TextField.h"
#include "MapEditor.h"
#include "MapPane.h"
#include "TilePane.h"
#include "TileMap.h"
#include "OutputPane.h"
#include "TileInfoPane.h"

class EditState : public AppState
{
public:
	// Constructor
	EditState(const sf::Font& f, MapEditor *m, TileMapInfo info);

	// Methods
	virtual void init();
	virtual void handleInput(Input *input);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

private:
	//TextField tileTexture;
	//TextField tileSize;
	//TextField tilesPerRow;
	//TextField mapX;
	//TextField mapY;
	int tpr;
	TilePane tileSet;
	MapPane map;
	OutputPane output;
	TileInfoPane tileInfo;

};

#endif