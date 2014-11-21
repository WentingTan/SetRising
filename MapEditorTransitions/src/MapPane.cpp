//==========================//
// MapPane.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "MapPane.h"

MapPane::MapPane(TileMap *pMap):
	map(pMap),
	bounds(115.0f, 0.0f, 685.0f, 600.0f)
{
	vscroll = NULL;
	hscroll = NULL;

	tile = NULL;
	index.x = 0;
	index.y = 0;

	float tSize = (float)map->getTileMapInfo().tileSize;
	highlight.setSize(sf::Vector2f(tSize, tSize));
	highlight.setFillColor(sf::Color(255, 255, 255, 0));
	highlight.setOutlineThickness(2);
	highlight.setOutlineColor(sf::Color::Yellow);

	selected = -2;
	newSel = false;
}

MapPane::~MapPane()
{
	if (vscroll)
		delete vscroll;
	if (hscroll)
		delete hscroll;
}

// tpr is tiles per row
void MapPane::init()
{
	TileMapInfo info = map->getTileMapInfo();
	vscroll = new VScrollBar(600.0f, 585.0f, (float)(info.mapSize.y * info.tileSize), sf::Vector2f(785.0f, 0.0f));
	hscroll = new HScrollBar(bounds.width - 16.0f, bounds.width - 15.0f, (float)(info.mapSize.x * info.tileSize), sf::Vector2f(115.0f, 585.0f));
}

void MapPane::setSelectedGraphic(int sel)
{
	selected = sel;
}


Tile* MapPane::getSelectedTile(int& x, int& y)
{
	x = index.x;
	y = index.y;
	return tile;
}

void MapPane::handleInput(Input *input)
{
	sf::Vector2f mousePos = input->getMousePos();
	newSel = false;

	if (bounds.contains(mousePos))
	{
		if (vscroll->handleInput(input) || hscroll->handleInput(input))
			return;

		if (input->wasPressed(InputNS::LEFT))
		{
			index = map->getTileIndex(mousePos.x - 115.0f, mousePos.y);
			tile = map->getTileByIndex(index.x, index.y);
			if (tile != NULL)
			{
				newSel = true;
				sf::FloatRect box = map->getTileHitBox(index.x, index.y);
				highlight.setPosition(box.left + 115.0f, box.top);
				if (selected > -1)
					tile->tileNum = selected;
				else if (selected == -1)
					tile->setDefault();
			}
		}
	}
}

bool MapPane::newSelected()
{
	return newSel;
}

void MapPane::update(float dt)
{
	vscroll->update(dt);
	hscroll->update(dt);
	sf::Vector2f scroll;
	scroll.x = hscroll->getScroll();
	scroll.y = vscroll->getScroll();
	highlight.move(-scroll.x, -scroll.y);

	map->scroll(scroll.x, scroll.y);
	map->update(dt);
}

void MapPane::draw(sf::RenderWindow& window)
{
	map->draw(window);
	window.draw(highlight);
	vscroll->draw(window);
	hscroll->draw(window);
}