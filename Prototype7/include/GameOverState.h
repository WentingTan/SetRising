//==========================//
// GameOverState.h          //
// Author: Matthew Stephens //
//==========================//
#ifndef _GAME_OVER_STATE_H_
#define _GAME_OVER_STATE_H_

#include "GameState.h"


class GameOverState : public GameState
{
public:
	// Constructor
	GameOverState(Game *game);
	// Destructor
	virtual ~GameOverState();

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
	static const int CONTINUE;
	static const int QUIT;
	static const float SELECTOR_SIZE;
	static const sf::Vector2f CONTINUE_POS;
	static const sf::Vector2f QUIT_POS;
};

#endif