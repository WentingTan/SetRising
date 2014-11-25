//==========================//
// MainMenuState.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "MainMenuState.h"
#include "Constants.h"
#include "Game.h"
#include "EventManager.h"
#include <fstream>
const sf::IntRect MainMenuState::SCREEN_RECT = sf::IntRect(0, 496, 320, 240);

const int MainMenuState::START = 0;
const int MainMenuState::EXIT = 1;
const float MainMenuState::SELECTOR_SIZE = 7.0f;
const sf::Vector2f MainMenuState::START_POS = sf::Vector2f(256.0f, 342.0f);
const sf::Vector2f MainMenuState::EXIT_POS = sf::Vector2f(256.0f, 374.0f);

//================================
// Constructor
//================================
MainMenuState::MainMenuState(Game *game):
	GameState(game)
{
	// Do nothing
}

//==============================
// Destructor
//==============================
MainMenuState::~MainMenuState()
{

}

// Methods
bool MainMenuState::init()
{
	screen.setTexture(*(pGame->getTexture(SCREENS)));
	screen.setTextureRect(SCREEN_RECT);
	screen.setScale(2.0f, 2.0f);

	selector.setPointCount(3);
	selector.setRadius(SELECTOR_SIZE);
	sf::FloatRect bounds = selector.getLocalBounds();
	selector.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	selector.rotate(90.0f);
	selector.setFillColor(sf::Color::White);
	selector.setPosition(START_POS);

	selected = START;

	return true;
}

void MainMenuState::handleInput(Input *input)
{
	if (input->wasPressed(InputNS::UP) || input->wasPressed(InputNS::DOWN))
	{
		if (selected == START)
			selected = EXIT;
		else
			selected = START;
	}

	if (input->wasPressed(InputNS::ENTER))
	{
		if (selected == START)
		{
			pGame->requestStateChange(GSCR_POP);
			pGame->requestStateChange(GSCR_PUSH_PLAY_STATE);
		}
		else if (selected == EXIT)
			pGame->requestStateChange(GSCR_EXIT);
	}
}

void MainMenuState::update(float dt)
{
	if (selected == START)
		selector.setPosition(START_POS);
	else
		selector.setPosition(EXIT_POS);
}

void MainMenuState::draw(sf::RenderWindow& window)
{
	window.draw(screen);
	window.draw(selector);
}