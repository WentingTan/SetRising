//==========================//
// MainMenuState.h        //
// Author: Gilbert Colón    //
//==========================//
#ifndef MAIN_MENU_STATE_H_
#define MAIN_MENU_STATE_H_

#include "GameState.h"
#include "Player.h"


class MainMenuState : public GameState
{
public:
	// Constructor
	MainMenuState(Game *game);
	// Destructor
	virtual ~MainMenuState();

	// Methods
	virtual bool init();
	virtual void handleInput(Input *input);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

protected:

	sf::Texture texture;
	sf::Sprite sprite;
};

#endif