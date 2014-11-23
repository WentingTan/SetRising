//==========================//
// MapEditor.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _MAP_EDITOR_H_
#define _MAP_EDITOR_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "TileMap.h"
#include "Input.h"

#include "AppState.h"

class MapEditor
{
public:
	// Constructor
	MapEditor();
	// Destructor
	~MapEditor();

	// Methods
	void init();
	void run();
	void requestStateChange(States::Change s);
	void loadTexture(std::string filename);
	sf::Texture* getTexture();
	void setTileMapInfo(TileMapInfo info);
	TileMap* getTileMap();
	void createTileMap();

private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time dt;
	sf::Font font;
	Input *input;

	sf::Texture texture;
	TileMap *map;

	TileMapInfo info;

	// State
	AppState *state;
	States::Change requested;
	bool change;

	// Helpers
	void changeState();
};

#endif