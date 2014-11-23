//==========================//
// MapEditor.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "MapEditor.h"
#include "MainMenu.h"
#include "NewMenu.h"
#include "EditState.h"
#include "LoadMenu.h"

MapEditor::MapEditor()
{
	input = NULL;
	state = NULL;
	change = false;
}

MapEditor::~MapEditor()
{
	if (input)
		delete input;
	if (state)
		delete state;
}

void MapEditor::init()
{
	// Create the window
	window.create(sf::VideoMode(1000, 675), "Map Editor", sf::Style::Close);

	// Initialize input
	input = new Input(window);

	// Load the font
	font.loadFromFile("arial.ttf");

	// Set the initial state to Main Menu and initialize it
	state = new MainMenu(font, this);
	state->init();

	map = new TileMap();
}

void MapEditor::loadTexture(std::string filename)
{
	texture.loadFromFile(filename);
}

sf::Texture* MapEditor::getTexture()
{
	return &texture;
}

void MapEditor::setTileMapInfo(TileMapInfo i)
{
	info = i;
}

TileMap* MapEditor::getTileMap()
{
	return map;
}

void MapEditor::createTileMap()
{
	map->create(&texture, info);
}

void MapEditor::run()
{
	while (window.isOpen())
	 {
		dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			else
				input->handleEvent(event);
        }

		// Get input
		input->getInput();

		// Handle input
		state->handleInput(input);
		// Update
		state->update(dt.asSeconds());
		// Draw
		window.clear();
		state->draw(window);
		window.display();

		// Change state if necessary
		if (change)
			changeState();

		// Clear the input
		input->clear();
    }
}

void MapEditor::requestStateChange(States::Change s)
{
	requested = s;
	change = true;
}

void MapEditor::changeState()
{
	AppState *temp = NULL;
	switch (requested)
	{
	case States::CREATE_NEW:
		temp = new NewMenu(font, this);
		break;
	case States::LOAD_FROM_FILE:
		temp = new LoadMenu(font, this);
		break;
	case States::EDIT:
		temp = new EditState(font, this, info);
		break;
	default:
		break;
	}

	// Deallocate the current state and transition to next state
	delete state;
	state = temp;
	state->init();

	change = false;
}