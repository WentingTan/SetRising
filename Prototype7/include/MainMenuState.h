//==========================//
// MainMenuState.h          //
// Author: Matthew Stephens //
//==========================//
#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include "GameState.h"


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
	sf::Sprite screen;
	sf::CircleShape selector;
	int selected;

	static const sf::IntRect SCREEN_RECT;
	static const int START;
	static const int EXIT;
	static const float SELECTOR_SIZE;
	static const sf::Vector2f START_POS;
	static const sf::Vector2f EXIT_POS;
};

#endif