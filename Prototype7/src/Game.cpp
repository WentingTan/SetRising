//==========================//
// Game.cpp                 //
// Author: Matthew Stephens //
//==========================//
#include "Game.h"
#include "GameState.h"
#include "PlayState.h"
#include "MessageState.h"
#include "GameOverState.h"
#include "MainMenuState.h"
#include "Audio.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
//==============================================================================
// Constructor
// Sets the state pointers to NULL, and sets the current number of states to 0.
//==============================================================================
Game::Game():
	n(0)
{
	for (int i = 0; i < MAX_STATES; i++)
		states[i] = NULL;
}

Game::~Game()
{

}

//===
// init()
//
//====
void Game::init()
{
	// Create the window
	window.create(sf::VideoMode((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT), GAME_NAME);
	hasFocus = true;
	
	// Create the input system
	input = new Input();

	audio = new Audio();
	audio->init();

	// Load textures used by the game
	textures[TILES].loadFromFile(TILE_TEXTURE);
	textures[PLAYER].loadFromFile(PLAYER_TEXTURE);
	textures[ENEMY].loadFromFile(ENEMY_TEXTURE);
	textures[LASER].loadFromFile(LASER_TEXTURE);
	textures[HBAR].loadFromFile(HBAR_TEXTURE);
	textures[HP].loadFromFile(HP_TEXTURE);
	textures[BKGD].loadFromFile(BKGD_TEXTURE);
	textures[DEATH].loadFromFile(DEATH_TEXTURE);
	textures[FREEZE].loadFromFile(FREEZE_TEXTURE);
	textures[SPIT].loadFromFile(SPIT_TEXTURE);
	textures[FLAME].loadFromFile(FLAME_TEXTURE);
	textures[CAVE_BKGD].loadFromFile(CAVE_BKGD_TEXTURE);
	textures[BAT].loadFromFile(BAT_TEXTURE);
	textures[BLACK_HOLE].loadFromFile(BLACKHOLE_TEXTURE);
	textures[GRAVITY].loadFromFile(GRAVITY_TEXTURE);
	textures[ENERGY].loadFromFile(ENERGY_TEXTURE);
	textures[CRAWLER].loadFromFile(CRAWLER_TEXTURE);
	textures[SCREENS].loadFromFile(SCREENS_TEXTURE);
	textures[ICE].loadFromFile(ICE_TEXTURE);

	// Seed the random number generator with the current time
	srand(time(NULL));

	// Push the play state onto the stack and initialize it
	//states[n] = new PlayState(this);
	//n++;
	//states[n-1]->init();
	processRequest(GSCR_PUSH_MAIN_MENU);
}


sf::Texture* Game::getTexture(int id)
{
	if (id >= 0 && id < NUM_TEXTURES)
		return &textures[id];
	else
		return NULL;
}

// main game loop
void Game::run()
{
	 while (window.isOpen())
	 {
		dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::LostFocus)
				hasFocus = false;
			if (event.type == sf::Event::GainedFocus)
				hasFocus = true;
        }

		if (hasFocus)
		{
			// Get input
			input->getInput();

			// Handle Input for the active state only
			states[n-1]->handleInput(input);

			// Update the active state only
			states[n-1]->update(dt.asSeconds());
			audio->update();

			// Render all states in order from bottom to top
			window.clear();
			for (int i = 0; i < n; i++)
				states[i]->draw(window);
			window.display();

			// Process any state change requests
			processStateChanges();
		}
    }
}

void Game::requestStateChange(int type)
{
	stateChangeRequests.push(type);
}

void Game::processStateChanges()
{
	while (!stateChangeRequests.empty())
	{
		int request = stateChangeRequests.front();
		stateChangeRequests.pop();
		processRequest(request);
	}
}

void Game::processRequest(int type)
{
	GameState *state = NULL;
	std::ofstream log("log.txt", std::ios::app);
	switch (type)
	{
	case GSCR_POP:
		pop();
		break;
	case GSCR_PUSH_MAIN_MENU:
		state = new MainMenuState(this);
		audio->registerHandlers();
		audio->playSong(TITLE_MUSIC);
		break;
	case GSCR_PUSH_PLAY_STATE:
		state = new PlayState(this);
		audio->playSong(START_MUSIC);
		break;
	case GSCR_PUSH_MSG_FLAME:
		state = new MessageState(this, MSG_GOT_FLAME);
		break;
	case GSCR_PUSH_MSG_FREEZE:
		state = new MessageState(this, MSG_GOT_FREEZE);
		break;
	case GSCR_PUSH_GAMEOVER:
		state = new GameOverState(this);
		break;
	case GSCR_CLEAR_STACK:
		clear();
		break;
	case GSCR_EXIT:
		clear();
		window.close();
		break;
	case GSCR_NONE:
	default:
		break;
	}
	log.close();
	if (state != NULL)
		push(state);
}

// Pops and deletes the top state in the state stack
void Game::pop()
{
	if (n == 0)
		return;

	delete states[n-1];
	states[n-1] = NULL;
	n--;
}

// pushes a state onto the stack and initializes it
void Game::push(GameState *state)
{
	if (n == MAX_STATES)
	{
		delete state;
		return;
	}

	states[n] = state;
	states[n]->init();
	n++;
}

void Game::clear()
{
	while (n > 0)
			pop();
}