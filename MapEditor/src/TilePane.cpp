//==========================//
// TilePane.cpp             //
// Author: Matthew Stephens //
//==========================//
#include "TilePane.h"

TilePane::TilePane(sf::Texture *texture, int nTiles, int tileSize):
	texture(texture),
	nTiles(nTiles),
	tileSize(tileSize),
	bounds(0.0f, 0.0f, 115.0f, 600.0f),
	background(sf::Vector2f(100.0f, 600.0f))
{
	tiles = NULL;
	vscroll = NULL;
	selected = -2;
	background.setFillColor(sf::Color(225, 225, 225));

	float scale = (float)tileSize / 32.0f;
	sf::IntRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.width = 32;
	rect.height = 32;
	tools.loadFromFile("tools.png");
	eraser.setTexture(tools);
	eraser.setTextureRect(rect);
	eraser.setScale(scale, scale);

	rect.left = 32;
	pointer.setTexture(tools);
	pointer.setTextureRect(rect);
	pointer.setScale(scale, scale);

	select.setSize(sf::Vector2f((float)tileSize, (float)tileSize));
	select.setOutlineThickness(4);
	select.setOutlineColor(sf::Color::Red);
	select.setFillColor(sf::Color(255,255,255, 0));
}

TilePane::~TilePane()
{
	if (tiles)
		delete [] tiles;
	if (vscroll)
		delete vscroll;
}

// tpr is tiles per row
void TilePane::init(int tpr)
{
	// Allocate space for the sprite array
	tiles = new sf::Sprite[nTiles];

	float hPadding = (background.getLocalBounds().width - tileSize) / 2.0f;
	float vPadding = hPadding > 50.0f ? 50.0f : hPadding;

	pointer.setPosition(hPadding, vPadding);
	eraser.setPosition(hPadding, 2.0f * vPadding + tileSize);

	for (int i = 0; i < nTiles; i++)
	{
		// Calculate the texture rect
		sf::IntRect rect;
		rect.left = (i % tpr) * tileSize;
		rect.top = (i / tpr) * tileSize;
		rect.width = tileSize;
		rect.height = tileSize;

		// Set the texture and texture rect for the sprite
		tiles[i].setTexture(*texture);
		tiles[i].setTextureRect(rect);

		// Position the sprite
		tiles[i].setPosition(hPadding, vPadding + (i + 2) * (vPadding + tileSize));
	}

	// Set up the vertical scroll bar
	vscroll = new VScrollBar(600.0f, 600.0f, vPadding + nTiles * (vPadding + tileSize), sf::Vector2f(100.0f, 0.0f));
}

int TilePane::getSelected() const
{
	return selected;
}


void TilePane::handleInput(Input *input)
{
	sf::Vector2f mousePos = input->getMousePos();

	if (bounds.contains(mousePos))
	{
		vscroll->handleInput(input);

		if (input->isPressed(InputNS::LEFT))
		{
			if (pointer.getGlobalBounds().contains(mousePos))
				selected = -2;
			else if (eraser.getGlobalBounds().contains(mousePos))
				selected = -1;
		}

		for (int i = 0; i < nTiles; i++)
		{
			if (tiles[i].getGlobalBounds().contains(mousePos))
			{
				tiles[i].setColor(sf::Color(225, 225, 225));
				if (input->isPressed(InputNS::LEFT))
					selected = i;
			}
			else
				tiles[i].setColor(sf::Color::White);
		}
	}
}

void TilePane::update(float dt)
{
	if (selected > -1)
		select.setPosition(tiles[selected].getPosition());
	else if (selected == -1)
		select.setPosition(eraser.getPosition());
	else if (selected == -2)
		select.setPosition(pointer.getPosition());

	vscroll->update(dt);
	float scroll = -1.0f * vscroll->getScroll();

	for (int i = 0; i < nTiles; i++)
		tiles[i].move(0.0f, scroll);

}

void TilePane::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(pointer);
	window.draw(eraser);
	for (int i = 0; i < nTiles; i++)
		window.draw(tiles[i]);
	window.draw(select);
	vscroll->draw(window);
}