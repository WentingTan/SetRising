//==========================//
// WinState.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "WinState.h"
#include "Constants.h"
#include "Game.h"
#include "EventManager.h"

const sf::IntRect WinState::SCREEN_RECT = sf::IntRect(0, 736, 320, 240);

const float WinState::DELAY = 10.0f;

//================================
// Constructor
//================================
WinState::WinState(Game *game):
	GameState(game)
{
	// Do nothing
}

//==============================
// Destructor
//==============================
WinState::~WinState()
{

}

// Methods
bool WinState::init()
{
	screen.setTexture(*(pGame->getTexture(SCREENS)));
	screen.setTextureRect(SCREEN_RECT);
	screen.setScale(2.0f, 2.0f);

	timer = 0.0f;

	return true;
}

void WinState::handleInput(Input *input)
{
	
}

void WinState::update(float dt)
{
	timer += dt;

	if (timer > DELAY)
	{
		pGame->requestStateChange(GSCR_CLEAR_STACK);
		pGame->requestStateChange(GSCR_PUSH_MAIN_MENU);
	}
}

void WinState::draw(sf::RenderWindow& window)
{
	window.draw(screen);
}