//==========================//
// Game.cpp                 //
// Author: Matthew Stephens //
//==========================//
#include "Game.h"
#include "GameState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "PauseMenuState.h"
#include <stdlib.h>
#include <time.h>

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

	// Seed the random number generator with the current time
	srand(time(NULL));

	// Push the play state onto the stack and initialize it
	//Push the Main menu state onto the stack and initializes it
	states[n] = new MainMenuState(this);
	states[n]->init();
	isMenu = true;
	isPaused = false;
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
			//Case to handle MainMenuState
			if (isMenu)
			{
				//Display menu Screen
				window.clear();
				states[n]->draw(window);
				window.display();

				// Get input from menu
				input->getInput();

				if (input->wasPressed(InputNS::NEWGAME)){

					//Clear the MainMenuState
					window.clear();

					//Replace MainMenuState with PlayState 
					states[n] = new PlayState(this);
					n++;
					states[n - 1]->init();
					isMenu = false;

				}
				else if (input->wasPressed(InputNS::QUIT)){
					window.close();
				}

			}
			else
			{
				// Get input
				input->getInput();

				//Not already paused
				if (!(isPaused) && input->wasPressed(InputNS::PAUSE)){
					states[n] = new PauseMenuState(this);
					n++;
					states[n - 1]->init();
					isPaused = true;
					states[n - 1]->draw(window);
					window.display();

				}
				//Already Paused
				else if (isPaused){

					if (input->wasPressed(InputNS::CONTINUE)){
						isPaused = false;
						n--;
					}
					else if (input->wasPressed(InputNS::QUIT)){
						window.close();
					}

				}
				else{
					// Handle Input for the active state only
					states[n - 1]->handleInput(input);

					// Update the active state only
					states[n - 1]->update(dt.asSeconds());

					// Render all states in order from bottom to top
					window.clear();
					for (int i = 0; i < n; i++)
						states[i]->draw(window);
					window.display();
				}
			}
		}
    }
}