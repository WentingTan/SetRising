//==========================//
// AppState.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _APP_STATE_H_
#define _APP_STATE_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "Input.h"
#include "TileMap.h"

namespace States
{
	enum Change
	{
		MAIN_MENU,
		CREATE_NEW,
		LOAD_FROM_FILE,
		EDIT
	};
}

// Forward declaration
class MapEditor;

class AppState
{
public:
	// Constructor
	AppState(const sf::Font& f, MapEditor *m) { font = f; app = m; }

	// Methods
	virtual void init() = 0;
	virtual void handleInput(Input *input) = 0;
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	sf::Font font;
	MapEditor *app;
};

#endif