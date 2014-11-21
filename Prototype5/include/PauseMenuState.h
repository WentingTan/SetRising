//==========================//
// PauseMenuState.h        //
// Author: Gilbert Colón    //
//==========================//
#ifndef PAUSE_MENU_STATE_H_
#define PAUSE_MENU_STATE_H_

#include "GameState.h"
#include "Player.h"


class PauseMenuState : public GameState
{
public:
	// Constructor
	PauseMenuState(Game *game);
	// Destructor
	virtual ~PauseMenuState();

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