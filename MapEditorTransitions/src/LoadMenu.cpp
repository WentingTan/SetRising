//==========================//
// LoadMenu.cpp              //
// Author: Matthew Stephens //
//==========================//
#include "LoadMenu.h"
#include <fstream>
#include "stdlib.h"
#include "TileMap.h"

LoadMenu::LoadMenu(const sf::Font& f, MapEditor *m):
	AppState(f, m),
	loadFile(f, "Load File", 25, 15)
{
	// Do nothing
}

// Methods
void LoadMenu::init()
{
	// Initialize title text
	title.setFont(font);
	title.setColor(sf::Color::Black);
	title.setString("Load Map From File");
	title.setCharacterSize(30);
	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	title.setPosition(500.0f, 75.0f);

	// Initialize the filename field
	loadFile.setPosition(sf::Vector2f(200.0f, 275.0f));
	loadFile.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the ok button
	sf::Vector2f size;
	size.x = 75.0f;
	size.y = 30.0f;
	std::string str = "Load";
	ok.setSize(size);
	ok.setText(font, str, 15);
	ok.setTextColors(sf::Color::Black, sf::Color(210, 210, 210));
	ok.setButtonColors(sf::Color(160, 160, 160), sf::Color(160, 160, 160), sf::Color(130,130,130), sf::Color(130,130,130));
	ok.setOutline(1, sf::Color::Black);
	ok.setActive(true);
	ok.setPosition(sf::Vector2f(640.0f, 350.0f));
}

void LoadMenu::handleInput(Input *input)
{
	loadFile.handleInput(input);
	ok.handleInput(input);
}

void LoadMenu::update(float dt)
{
	if (ok.wasClicked())
	{
		// Open the file and read in the texture file name
		std::string load = loadFile.getEnteredText();
		std::ifstream file(load.c_str());
		std::string tFile;
		file >> tFile;

		// Read in some tile map info (needed by EditState)
		TileMapInfo info;
		file >> info.nTiles;
		file >> info.tileSize;
		file >> info.tpr;
		file.close();

		// Load the texture
		app->loadTexture(tFile);

		// Send the tile map info to the map editor
		app->setTileMapInfo(info);

		// Load the tile map
		app->getTileMap()->loadFromFile(load);

		// Request a state change
		app->requestStateChange(States::EDIT);
	}
}

void LoadMenu::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(190, 190, 190));
	window.draw(title);
	loadFile.draw(window);
	ok.draw(window);
}