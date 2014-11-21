//==========================//
// MainMenu.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "AppState.h"
#include "Button.h"
#include "MapEditor.h"


class MainMenu : public AppState
{
public:
	// Constructor
	MainMenu(const sf::Font& f, MapEditor *m);

	// Methods
	virtual void init();
	virtual void handleInput(Input *input);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

private:
	sf::Text title;
	Button newMap;
	Button loadMap;
};

#endif