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

const int NUM_TEXTURES = 5;
const char TILE_TEXTURE[] = "tiles1.png";
const char PLAYER_TEXTURE[] = "setsprite.png";
const char ENEMY_TEXTURE[] = "set.png";
const char LASER_TEXTURE[] = "laser.png";
const char BOSS_TEXTURE[] = "enemy3cut.png";

// Texture ID's
const int TILES = 0;
const int PLAYER = 1;
const int ENEMY = 2;
const int LASER = 3;
const int BOSS = 4;

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