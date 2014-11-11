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

// NOTE: Before completion, we will consolidate all textures into as few textures
// as possible.
const int NUM_TEXTURES = 6;
const char TILE_TEXTURE[] = "tiles.png";
const char PLAYER_TEXTURE[] = "setsprite.png";
const char ENEMY_TEXTURE[] = "set.png";
const char LASER_TEXTURE[] = "laser.png";
const char HBAR_TEXTURE[] = "hbar.png";
const char HP_TEXTURE[] = "hp.png";

// Texture ID's
const int TILES = 0;
const int PLAYER = 1;
const int ENEMY = 2;
const int LASER = 3;
const int HBAR = 4;
const int HP = 5;

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