//==========================//
// PlayState.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "PlayState.h"
#include "Game.h"

//================================
// Constructor
//================================
PlayState::PlayState(Game *game):
	GameState(game)
{

}

//==============================
// Destructor
//==============================
PlayState::~PlayState()
{

}

// Methods
bool PlayState::init()
{
	tmap.setTexture(pGame->getTexture(TILES));
	tmap.loadFromFile("enemymap.txt");
	tmap.init();

	player.setTexture(pGame->getTexture(PLAYER));
	player.init();
	player.setTileMap(&tmap);
	
	/*boss.setTexture(pGame->getTexture(BOSS));
	boss.init();
	boss.setTileMap(&tmap);
	*/
	enemies.init(pGame->getTexture(ENEMY), pGame->getTexture(BOSS), &tmap);

    pProjectiles.init(pGame->getTexture(LASER));

    player.setProjectiles(&pProjectiles);

	return true;
}

void PlayState::handleInput(Input *input)
{
	player.handleInput(*input);
}

void PlayState::update(float dt)
{
	player.update(dt);
	tmap.update(dt);
	enemies.update(dt);
    pProjectiles.update(dt);
	//boss.update(dt);

	pProjectiles.checkCollisions(&enemies);
}

void PlayState::draw(sf::RenderWindow& window)
{
	tmap.draw(window);
	pProjectiles.draw(window);
	player.draw(window);
	enemies.draw(window);
	//boss.draw(window);
}