//==========================//
// GameOverState.cpp        //
// Author: Matthew Stephens //
//==========================//
#include "GameOverState.h"
#include "Constants.h"
#include "Game.h"
#include "EventManager.h"
#include <fstream>
const sf::IntRect GameOverState::SCREEN_RECT = sf::IntRect(0, 256, 320, 240);

const int GameOverState::CONTINUE = 0;
const int GameOverState::QUIT = 1;
const float GameOverState::SELECTOR_SIZE = 8.0f;
const sf::Vector2f GameOverState::CONTINUE_POS = sf::Vector2f(284.0f, 286.0f);
const sf::Vector2f GameOverState::QUIT_POS = sf::Vector2f(284.0f, 330.0f);

//================================
// Constructor
//================================
GameOverState::GameOverState(Game *game):
	GameState(game)
{
	// Do nothing
}

//==============================
// Destructor
//==============================
GameOverState::~GameOverState()
{

}

// Methods
bool GameOverState::init()
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
	selector.setPosition(CONTINUE_POS);

	selected = CONTINUE;

	return true;
}

void GameOverState::handleInput(Input *input)
{
	if (input->wasPressed(InputNS::UP) || input->wasPressed(InputNS::DOWN))
	{
		if (selected == CONTINUE)
			selected = QUIT;
		else
			selected = CONTINUE;
	}

	std::ofstream log("log.txt", std::ios::app);


	if (input->wasPressed(InputNS::ENTER))
	{
		if (selected == CONTINUE)
		{
			Event::Data e;
			e.type = Event::CONTINUE;
			EventManager::triggerEvent(e);
			pGame->requestStateChange(GSCR_POP);
		}
		else if (selected == QUIT)
		{
			EventManager::clearHandlers();
			pGame->requestStateChange(GSCR_CLEAR_STACK);
			pGame->requestStateChange(GSCR_PUSH_MAIN_MENU);
		}
	}
}

void GameOverState::update(float dt)
{
	if (selected == CONTINUE)
		selector.setPosition(CONTINUE_POS);
	else
		selector.setPosition(QUIT_POS);
}

void GameOverState::draw(sf::RenderWindow& window)
{
	window.draw(screen);
	window.draw(selector);
}