//==========================//
// LoadMenu.h               //
// Author: Matthew Stephens //
//==========================//
#ifndef _LOAD_MENU_H_
#define _LOAD_MENU_H_

#include "AppState.h"
#include "Button.h"
#include "TextField.h"
#include "MapEditor.h"

class LoadMenu : public AppState
{
public:
	// Constructor
	LoadMenu(const sf::Font& f, MapEditor *m);

	// Methods
	virtual void init();
	virtual void handleInput(Input *input);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

private:
	sf::Text title;
	Button ok;

	TextField loadFile;
};

#endif