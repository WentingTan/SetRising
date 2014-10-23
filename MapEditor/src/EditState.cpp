//==========================//
// EditState.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "EditState.h"
#include <fstream>
#include "stdlib.h"

EditState::EditState(const sf::Font& f, MapEditor *m, TileMapInfo info):
	AppState(f, m),
	tpr(info.tpr),
	tileSet(app->getTexture(), info.nTiles, info.tileSize),
	map(app->getTileMap()),
	output(f, app->getTileMap()),
	tileInfo(f)
{
	// Do nothing
}

// Methods
void EditState::init()
{
	tileSet.init(tpr);
	map.init();
	output.init();
	tileInfo.init();
}

void EditState::handleInput(Input *input)
{
	tileSet.handleInput(input);
	map.handleInput(input);
	output.handleInput(input);
	tileInfo.handleInput(input);
}

void EditState::update(float dt)
{
	map.setSelectedGraphic(tileSet.getSelected());
	tileSet.update(dt);
	map.update(dt);
	output.update(dt);

	if (map.newSelected())
	{
		sf::Vector2i ind;
		Tile *t = map.getSelectedTile(ind.x, ind.y);
		tileInfo.getTileInfo(t, ind);
	}

	tileInfo.update(dt);
}

void EditState::draw(sf::RenderWindow& window)
{
	map.draw(window);
	tileSet.draw(window);
	output.draw(window);
	tileInfo.draw(window);
}