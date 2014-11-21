//==========================//
// NewMenu.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "NewMenu.h"
#include <fstream>
#include "stdlib.h"
#include "TileMap.h"

NewMenu::NewMenu(const sf::Font& f, MapEditor *m):
	AppState(f, m),
	tileTexture(f, "Tile Texture", 25, 15),
	nTiles(f, "Number of Tiles", 25, 3),
	tileSize(f, "Tile Size", 25, 3),
	tilesPerRow(f, "Tiles Per Row", 25, 3),
	mapX(f, "Map Size", 25, 3),
	mapY(f, "x", 25, 3)
{
	// Do nothing
}

// Methods
void NewMenu::init()
{
	// Initialize title text
	title.setFont(font);
	title.setColor(sf::Color::Black);
	title.setString("Create New Map");
	title.setCharacterSize(30);
	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	title.setPosition(500.0f, 75.0f);

	// Initialize the tileTexture field
	tileTexture.setPosition(sf::Vector2f(196.0f, 175.0f));
	tileTexture.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the nTiles field
	nTiles.setPosition(sf::Vector2f(145.0f, 235.0f));
	nTiles.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the tileSize field
	tileSize.setPosition(sf::Vector2f(226.0f, 295.0f));
	tileSize.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the tilesPerRow field
	tilesPerRow.setPosition(sf::Vector2f(166.0f, 355.0f));
	tilesPerRow.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the mapX field
	mapX.setPosition(sf::Vector2f(218.0f, 415.0f));
	mapX.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the mapY field
	mapY.setPosition(sf::Vector2f(441.0f, 418.0f));
	mapY.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the ok button
	sf::Vector2f size;
	size.x = 75.0f;
	size.y = 30.0f;
	std::string str = "OK";
	ok.setSize(size);
	ok.setText(font, str, 15);
	ok.setTextColors(sf::Color::Black, sf::Color(210, 210, 210));
	ok.setButtonColors(sf::Color(160, 160, 160), sf::Color(160, 160, 160), sf::Color(130,130,130), sf::Color(130,130,130));
	ok.setOutline(1, sf::Color::Black);
	ok.setActive(true);
	ok.setPosition(sf::Vector2f(750.0f, 550.0f));
}

void NewMenu::handleInput(Input *input)
{
	tileTexture.handleInput(input);
	nTiles.handleInput(input);
	tileSize.handleInput(input);
	tilesPerRow.handleInput(input);
	mapX.handleInput(input);
	mapY.handleInput(input);
	ok.handleInput(input);
}

void NewMenu::update(float dt)
{
	if (ok.wasClicked())
	{
		// Load the texture
		app->loadTexture(tileTexture.getEnteredText());

		// Send the rest of the info to the MapEditor
		TileMapInfo info;
		info.textureFile = std::string(tileTexture.getEnteredText());
		info.nTiles = atoi(nTiles.getEnteredText().c_str());
		info.tileSize = atoi(tileSize.getEnteredText().c_str());
		info.tpr = atoi(tilesPerRow.getEnteredText().c_str());
		info.mapSize.x = atoi(mapX.getEnteredText().c_str());
		info.mapSize.y = atoi(mapY.getEnteredText().c_str());

		app->setTileMapInfo(info);
		app->createTileMap();
		// Request a state change
		app->requestStateChange(States::EDIT);
	}
}

void NewMenu::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(190, 190, 190));
	window.draw(title);
	tileTexture.draw(window);
	nTiles.draw(window);
	tileSize.draw(window);
	tilesPerRow.draw(window);
	mapX.draw(window);
	mapY.draw(window);
	ok.draw(window);
}