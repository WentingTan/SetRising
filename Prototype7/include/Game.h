//==========================//
// Game.h                   //
// Author: Matthew Stephens //
//==========================//
#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Constants.h"
#include <queue>

class GameState;
class Audio;

const char GAME_NAME[] = "Platform Demo 2";
const int MAX_STATES = 8;

// NOTE: Before completion, we will consolidate all textures into as few textures
// as possible.
const int NUM_TEXTURES = 20;
const char TILE_TEXTURE[] = "tiles.png";
const char PLAYER_TEXTURE[] = "setsprite.png";
const char ENEMY_TEXTURE[] = "SnakeEnemy.png";
const char LASER_TEXTURE[] = "laser.png";
const char HBAR_TEXTURE[] = "hbar.png";
const char HP_TEXTURE[] = "hp.png";
const char BKGD_TEXTURE[] = "bkgd.png";
const char DEATH_TEXTURE[] = "deaths.png";
const char FREEZE_TEXTURE[] = "freeze_ray.png";
const char SPIT_TEXTURE[] = "spit.png";
const char FLAME_TEXTURE[] = "flame.png";
const char CAVE_BKGD_TEXTURE[] = "cave_bkgd.png";
const char BAT_TEXTURE[] = "bat.png";
const char BLACKHOLE_TEXTURE[] = "blackhole.png";
const char GRAVITY_TEXTURE[] = "gravity.png";
const char ENERGY_TEXTURE[] = "weapons.png";
const char CRAWLER_TEXTURE[] = "crawler.png";
const char SCREENS_TEXTURE[] = "screens.png";
const char ICE_TEXTURE[] = "iceblock.png";
const char BOSS_TEXTURE[] = "metroid_boss.png";

// Texture ID's
const int TILES = 0;
const int PLAYER = 1;
const int ENEMY = 2;
const int LASER = 3;
const int HBAR = 4;
const int HP = 5;
const int BKGD = 6;
const int DEATH = 7;
const int FREEZE = 8;
const int SPIT = 9;
const int FLAME = 10;
const int CAVE_BKGD = 11;
const int BAT = 12;
const int BLACK_HOLE = 13;
const int GRAVITY = 14;
const int ENERGY = 15;
const int CRAWLER = 16;
const int SCREENS = 17;
const char ICE = 18;
const int BOSS = 19;

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
	void requestStateChange(int type);

	sf::Texture* getTexture(int id);

private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time dt;

	GameState *states[MAX_STATES];
	int n;
	bool hasFocus;
	std::queue<int> stateChangeRequests;

	// Input
	Input *input;
	// Audio
	Audio *audio;

	// Resources
	sf::Texture textures[NUM_TEXTURES];

	// Helpers
	void clear();
	void pop();
	void push(GameState *state);
	void processStateChanges();
	void processRequest(int type);
};

#endif