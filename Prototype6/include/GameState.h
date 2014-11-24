//==========================//
// GameState.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <SFML/Graphics.hpp>

// Forward declaration
class Game;
class Input;

class GameState
{
public:
	// Constructor
	GameState(Game *game) { pGame = game; }
	// Destructor
	virtual ~GameState() {}

	// Methods
	virtual bool init() = 0;
	virtual void handleInput(Input *input) = 0;
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	Game *pGame;
};

#endif