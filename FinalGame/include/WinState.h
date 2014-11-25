//==========================//
// WinState.h          //
// Author: Matthew Stephens //
//==========================//
#ifndef _WIN_STATE_H_
#define _WIN_STATE_H_

#include "GameState.h"


class WinState : public GameState
{
public:
	// Constructor
	WinState(Game *game);
	// Destructor
	virtual ~WinState();

	// Methods
	virtual bool init();
	virtual void handleInput(Input *input);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

protected:
	sf::Sprite screen;
	float timer;

	static const sf::IntRect SCREEN_RECT;
	static const float DELAY;

};

#endif