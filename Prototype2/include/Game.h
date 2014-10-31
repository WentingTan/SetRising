//==========================//
// Game.h                   //
// Author: Matthew Stephens //
//==========================//
#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>
#include "Input.h"

class GameState;

const char GAME_NAME[] = "Platform Demo 2";
const int MAX_STATES = 8;

const int NUM_TEXTURES = 3;
const char TILE_TEXTURE[] = "tiles.png";
const char PLAYER_TEXTURE[] = "mm.png";
const char BOSS_TEXTURE[] = "enemy3cut.png";

const int TILES = 0;
const int PLAYER = 1;
const int BOSS = 2;

class Game
{
public:
	// Constructor
	Game();
	// Destructor
	~Game();

	// Methods
	void init();
	void run();

	sf::Texture* getTexture(int id);

private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time dt;

	GameState *states[MAX_STATES];
	int n;
	bool hasFocus;
	
	// Input
	Input *input;

	// Resources
	sf::Texture textures[NUM_TEXTURES];
};

#endif